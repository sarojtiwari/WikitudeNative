//
//  StrokedRectangle.swift
//  Native Examples
//
//  Created by Max Meraner on 10/04/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import GLKit

class StrokedRectangle
{
    public var scale: Float!
    
    var augmentationProgram:    GLuint!
    var positionSlot:           GLuint!
    var projectUniform:         GLuint!
    var modelViewUniform:       GLuint!
    var colorSlot:              GLuint!
    
    var projection:             GLKMatrix4!
    var modelView:              GLKMatrix4!
    
    var internalColor:          GLKVector4!
    
    init()
    {
        scale = 1
        projection = GLKMatrix4Identity
        modelView = GLKMatrix4Identity
        internalColor = GLKVector4Make(1.0, 0.58, 0.16, 1.0)
    }
    
    // MARK: - Public Methods
    func setProjectionMatrix(_ projectionMatrix: UnsafePointer<Float>)
    {
        memcpy(&self.projection.m, projectionMatrix, 16 * MemoryLayout<Float>.size)
    }
    
    func setModelViewMatrix(_ modelViewMatrix: UnsafePointer<Float>)
    {
        memcpy(&self.modelView.m, modelViewMatrix, 16 * MemoryLayout<Float>.size)
    }
    
    func setColor(_ color: UIColor)
    {
        var red: CGFloat = 0
        var green: CGFloat = 0
        var blue: CGFloat = 0
        var alpha: CGFloat = 0
        if color.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        {
            self.internalColor = GLKVector4Make(Float(red), Float(green), Float(blue), Float(alpha))
        }
    }
    
    func releaseProgram()
    {
        if nil != self.augmentationProgram
        {
            glDeleteProgram(self.augmentationProgram)
            self.augmentationProgram = 0
        }
    }
    
    func draw(in context: EAGLContext)
    {
        EAGLContext.setCurrent(context)
        if ( nil == self.augmentationProgram )
        {
            compileShaders()
            
            WT_GL_ASSERT_AND_RETURN( &self.positionSlot, GLuint(glGetAttribLocation(self.augmentationProgram, "v_position")) )
            
            WT_GL_ASSERT_AND_RETURN( &self.projectUniform, GLuint(glGetUniformLocation(self.augmentationProgram, "Projection")) )
            WT_GL_ASSERT_AND_RETURN( &self.modelViewUniform, GLuint(glGetUniformLocation(self.augmentationProgram, "Modelview")) )
            
            WT_GL_ASSERT_AND_RETURN( &self.colorSlot, GLuint(glGetUniformLocation(self.augmentationProgram, "Color")) )
            
            WT_GL_ASSERT( glDisable(GLenum(GL_DEPTH_TEST)) )
            WT_GL_ASSERT( glLineWidth(10.0) )
        }
        
        WT_GL_ASSERT( glDisable(GLenum(GL_DEPTH_TEST)) )
        WT_GL_ASSERT( glUseProgram(self.augmentationProgram) )
        
        /* reset any previously bound buffer */
        WT_GL_ASSERT( glBindBuffer(GLenum(GL_ARRAY_BUFFER), 0) )
        WT_GL_ASSERT( glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), 0) )
        
        let rectVerts : [GLfloat] = [ -0.5, -0.5, 0.0,
                                      -0.5,  0.5, 0.0,
                                       0.5,  0.5, 0.0,
                                       0.5, -0.5, 0.0 ]
        
        // Load the vertex position
        WT_GL_ASSERT( glVertexAttribPointer(self.positionSlot, 3, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 0, rectVerts) )
        WT_GL_ASSERT( glEnableVertexAttribArray(self.positionSlot) )
        
        let copyProjection = self.projection.m;
        withUnsafePointer(to: &self.projection.m)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: copyProjection))
            {
                WT_GL_ASSERT( glUniformMatrix4fv(Int32(self.projectUniform), 1, 0, $0) )
            }
        }
        
        let scaleMatrix: GLKMatrix4 = GLKMatrix4MakeScale(self.scale, self.scale, 1.0)
        var finalModelViewMatrix: GLKMatrix4 = GLKMatrix4Multiply(self.modelView, scaleMatrix)
        let copyFMVMatrix = finalModelViewMatrix.m
        withUnsafePointer(to: &finalModelViewMatrix.m)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: copyFMVMatrix))
            {
                WT_GL_ASSERT( glUniformMatrix4fv(Int32(self.modelViewUniform), 1, 0, $0) )
            }
        }
        
        let color = internalColor.v
        withUnsafePointer(to: &internalColor.v)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: color))
            {
                WT_GL_ASSERT( glUniform4fv(Int32(self.colorSlot), 1, $0) )
            }
        }
        
        let indices : [GLushort] = [0, 1, 2, 3]
        WT_GL_ASSERT( glDrawElements(GLenum(GL_LINE_LOOP), GLsizei(indices.count), GLenum(GL_UNSIGNED_SHORT), indices) )
    }
    
    // MARK: - Private Methods
    // MARK: OpenGLES 2
    private func compileShader(_ shaderName: String, withType shaderType:GLenum) -> GLuint
    {
        let shaderPath: String! = Bundle.main.path(forResource: shaderName, ofType: "glsl")
        var shaderString: String
        
        do
        {
            shaderString = try String(contentsOfFile: shaderPath, encoding: String.Encoding.utf8)
        }
        catch let error
        {
            print("Error loading shader: \(error.localizedDescription)")
            exit(1)
        }
        
        let shaderHandle: GLuint = glCreateShader(shaderType)
        
        let shaderStringUTF8 = shaderString.cString(using: String.defaultCStringEncoding)
        var shaderStringUTF8Pointer:UnsafePointer<GLchar>? = UnsafePointer(shaderStringUTF8)
        
        var shaderStringLength: GLint = GLint(shaderString.count)
        
        WT_GL_ASSERT( glShaderSource(shaderHandle, GLsizei(1), &shaderStringUTF8Pointer, &shaderStringLength) )
        WT_GL_ASSERT( glCompileShader(shaderHandle) )
        
        var compileSuccess: GLint = 0
        WT_GL_ASSERT( glGetShaderiv(shaderHandle, GLenum(GL_COMPILE_STATUS), &compileSuccess) )
        if ( GL_FALSE == compileSuccess )
        {
            let bufferLength: GLsizei = 256
            var messages: [GLchar] = Array(repeating: GLchar(0), count: Int(bufferLength))
            var actualLength: GLsizei = 0
            glGetShaderInfoLog(shaderHandle, bufferLength, &actualLength, &messages)
            print(String(validatingUTF8: messages)!)
            exit(1)
        }
        
        return shaderHandle
    }
    
    private func compileShaders()
    {
        let vertexShader: GLuint = compileShader("VertexShader", withType: GLenum(GL_VERTEX_SHADER))
        let fragmentShader: GLuint = compileShader("FragmentShader", withType: GLenum(GL_FRAGMENT_SHADER))
        
        self.augmentationProgram = glCreateProgram()
        
        WT_GL_ASSERT( glAttachShader(self.augmentationProgram, vertexShader) )
        WT_GL_ASSERT( glAttachShader(self.augmentationProgram, fragmentShader) )
        WT_GL_ASSERT( glLinkProgram(self.augmentationProgram) )
        
        WT_GL_ASSERT( glDeleteShader(vertexShader) )
        WT_GL_ASSERT( glDeleteShader(fragmentShader) )
        
        var linkSuccess: GLint = 0
        glGetProgramiv(self.augmentationProgram, GLenum(GL_LINK_STATUS), &linkSuccess)
        if ( GL_FALSE == linkSuccess )
        {
            let bufferLength: GLsizei = 256
            var messages: [GLchar] = Array(repeating: GLchar(0), count: Int(bufferLength))
            var actualLength: GLsizei = 0
            glGetProgramInfoLog(self.augmentationProgram, bufferLength, &actualLength, &messages)
            print(String(validatingUTF8: messages)!)
            exit(1)
        }
    }
}
