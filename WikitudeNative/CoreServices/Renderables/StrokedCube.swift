//
//  StrokedCube.swift
//  Native Examples
//
//  Created by Max Meraner on 10/04/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import GLKit

class StrokedCube: CubeBase
{
    var colorSlot:              GLuint!
    
    var internalColor:          GLKVector4!
    
    override init()
    {
        super.init()
        
        internalColor = GLKVector4Make(1.0, 0.58, 0.16, 1.0)
    }
    
    // MARK: - Public Methods
    
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
    
    func draw(in context: EAGLContext)
    {
        EAGLContext.setCurrent(context)
        if ( nil == self.augmentationProgram )
        {
            self.linkShaderObject(with: "VertexShader", and: "FragmentShader")
            
            WT_GL_ASSERT_AND_RETURN( &self.positionSlot, GLuint(glGetAttribLocation(self.augmentationProgram, "v_position")) )
            
            WT_GL_ASSERT_AND_RETURN( &self.projectionUniform, GLuint(glGetUniformLocation(self.augmentationProgram, "Projection")) )
            WT_GL_ASSERT_AND_RETURN( &self.modelViewUniform, GLuint(glGetUniformLocation(self.augmentationProgram, "Modelview")) )
            
            WT_GL_ASSERT_AND_RETURN( &self.colorSlot, GLuint(glGetUniformLocation(self.augmentationProgram, "Color")) )
        }
        
        WT_GL_ASSERT( glDisable(GLenum(GL_DEPTH_TEST)) )
        WT_GL_ASSERT( glUseProgram(self.augmentationProgram) )
        
        /* reset any previously bound buffer */
        WT_GL_ASSERT( glBindBuffer(GLenum(GL_ARRAY_BUFFER), 0) )
        WT_GL_ASSERT( glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), 0) )
        
        let cubeVerts : [GLfloat] = [ -0.5, -0.5,  0.5,
                                      -0.5,  0.5,  0.5,
                                       0.5,  0.5,  0.5,
                                       0.5, -0.5,  0.5,
                                       0.5, -0.5, -0.5,
                                       0.5,  0.5, -0.5,
                                       0.5,  0.5,  0.5,
                                       0.5,  0.5, -0.5,
                                      -0.5,  0.5, -0.5,
                                      -0.5, -0.5, -0.5,
                                       0.5, -0.5, -0.5,
                                      -0.5, -0.5, -0.5,
                                      -0.5,  0.5, -0.5,
                                      -0.5,  0.5,  0.5,
                                      -0.5, -0.5,  0.5,
                                       0.5, -0.5,  0.5,
                                      -0.5, -0.5,  0.5,
                                      -0.5, -0.5, -0.5 ]
    
        // Load the vertex position
        WT_GL_ASSERT( glVertexAttribPointer(self.positionSlot, 3, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 0, cubeVerts) )
        WT_GL_ASSERT( glEnableVertexAttribArray(self.positionSlot) )
    
        let projectionMatrixCopy = self.projection.m
        withUnsafePointer(to: &self.projection.m)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: projectionMatrixCopy))
            {
                WT_GL_ASSERT( glUniformMatrix4fv(Int32(self.projectionUniform), 1, 0, $0) )
            }
        }
        
        let translationMatrix: GLKMatrix4 = GLKMatrix4MakeTranslation(Float(self.xTranslation), Float(self.yTranslation), Float(self.zTranslation))
        let scaleMatrix: GLKMatrix4 = GLKMatrix4MakeScale(Float(self.xScale * self.uniformScale), Float(self.yScale * self.uniformScale), Float(self.zScale * self.uniformScale))
        
        let modelMatrix = GLKMatrix4Multiply(translationMatrix, scaleMatrix)
        var finalModelViewMatrix: GLKMatrix4 = GLKMatrix4Multiply(self.modelView, modelMatrix)
        let copyFMVMatrix = finalModelViewMatrix.m
        withUnsafePointer(to: &finalModelViewMatrix.m)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue:copyFMVMatrix))
            {
                WT_GL_ASSERT( glUniformMatrix4fv(Int32(self.modelViewUniform), 1, 0, $0) )
            }
        }
        
        let internalColorCopy = internalColor.v;
        withUnsafePointer(to: &internalColor.v)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: internalColorCopy))
            {
                WT_GL_ASSERT( glUniform4fv(Int32(self.colorSlot), 1, $0) )
            }
        }
        
        WT_GL_ASSERT( glEnable(GLenum(GL_DEPTH_TEST)) )
        WT_GL_ASSERT( glLineWidth(10.0) )
        
        let indices : [GLushort] = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]
        WT_GL_ASSERT( glDrawElements(GLenum(GL_LINE_LOOP), GLsizei(indices.count), GLenum(GL_UNSIGNED_SHORT), indices) )
        
        WT_GL_ASSERT( glLineWidth(1.0) )
    }
}
