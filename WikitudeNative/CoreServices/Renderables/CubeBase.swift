//
//  CubeBase.swift
//  Native Examples
//
//  Created by Max Meraner on 27/06/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import GLKit

class CubeBase
{
    var uniformScale:           CGFloat!
    
    var xScale:                 CGFloat!
    var yScale:                 CGFloat!
    var zScale:                 CGFloat!
    
    var xTranslation:           CGFloat!
    var yTranslation:           CGFloat!
    var zTranslation:           CGFloat!
    
    var augmentationProgram:    GLuint!
    var positionSlot:           GLuint!
    var projectionUniform:      GLuint!
    var modelViewUniform:       GLuint!
    
    var projection:             GLKMatrix4!
    var modelView:              GLKMatrix4!
    
    init()
    {
        uniformScale = 1.0
        
        xScale = 1.0
        yScale = 1.0
        zScale = 1.0
        
        xTranslation = 0.0
        yTranslation = 0.0
        zTranslation = 0.0
        
        projection = GLKMatrix4Identity
        modelView = GLKMatrix4Identity
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
    
    func releaseProgram()
    {
        if nil != self.augmentationProgram
        {
            glDeleteProgram(self.augmentationProgram)
            self.augmentationProgram = 0
        }
    }
    
    // MARK: - OpenGLES 2
    
    func compileShader(_ shaderName: String, withType shaderType:GLenum) -> GLuint
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
    
    func linkShaderObject(with vertexShaderFileName: String, and fragmentShaderFileName: String)
    {
        let vertexShader: GLuint = compileShader(vertexShaderFileName, withType: GLenum(GL_VERTEX_SHADER))
        let fragmentShader: GLuint = compileShader(fragmentShaderFileName, withType: GLenum(GL_FRAGMENT_SHADER))
        
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
