//
//  OccluderCube.swift
//  Native Examples
//
//  Created by Max Meraner on 27/06/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import GLKit

class OccluderCube: CubeBase
{
    override init()
    {
        super.init()
    }
    
    // MARK: - Public Methods
    
    func draw(in context: EAGLContext)
    {
        EAGLContext.setCurrent(context)
        if ( nil == self.augmentationProgram )
        {
            self.linkShaderObject(with: "VertexShader", and: "FragmentShaderOccluder")
            
            WT_GL_ASSERT_AND_RETURN( &self.positionSlot, GLuint(glGetAttribLocation(self.augmentationProgram, "v_position")) )
            
            WT_GL_ASSERT_AND_RETURN( &self.projectionUniform, GLuint(glGetUniformLocation(self.augmentationProgram, "Projection")) )
            WT_GL_ASSERT_AND_RETURN( &self.modelViewUniform, GLuint(glGetUniformLocation(self.augmentationProgram, "Modelview")) )
        }
        
        WT_GL_ASSERT( glUseProgram(self.augmentationProgram) )
        
        // reset any previously bound buffer
        WT_GL_ASSERT( glBindBuffer(GLenum(GL_ARRAY_BUFFER), 0) )
        WT_GL_ASSERT( glBindBuffer(GLenum(GL_ELEMENT_ARRAY_BUFFER), 0) )
        
        let cubeVerts : [GLfloat] = [ -0.5,  0.5,  0.5,
                                      -0.5, -0.5,  0.5,
                                       0.5,  0.5,  0.5,
                                       0.5, -0.5,  0.5,
                                      -0.5,  0.5, -0.5,
                                      -0.5, -0.5, -0.5,
                                       0.5,  0.5, -0.5,
                                       0.5, -0.5, -0.5, ]
        
        let cubeIndices : [GLushort] = [1, 0, 2,
                                    2, 3, 1,
                                    7, 6, 4,
                                    4, 5, 7,
                                    0, 4, 6,
                                    6, 2, 0,
                                    5, 1, 3,
                                    3, 7, 5,
                                    3, 2, 6,
                                    6, 7, 3,
                                    5, 4, 0,
                                    0, 1, 5]
        
        // Load the vertex position
        WT_GL_ASSERT( glVertexAttribPointer(self.positionSlot, 3, GLenum(GL_FLOAT), GLboolean(GL_FALSE), 0, cubeVerts) )
        WT_GL_ASSERT( glEnableVertexAttribArray(self.positionSlot) )
        let copyProjection = self.projection.m
        withUnsafePointer(to: &self.projection.m)
        {
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: copyProjection))
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
            $0.withMemoryRebound(to: GLfloat.self, capacity: MemoryLayout.size(ofValue: copyFMVMatrix))
            {
                WT_GL_ASSERT( glUniformMatrix4fv(Int32(self.modelViewUniform), 1, 0, $0) )
            }
        }
        
        WT_GL_ASSERT( glEnable(GLenum(GL_DEPTH_TEST)) )
        WT_GL_ASSERT( glDepthMask(GLboolean(GL_TRUE)) )
        WT_GL_ASSERT( glColorMask(GLboolean(GL_FALSE), GLboolean(GL_FALSE), GLboolean(GL_FALSE), GLboolean(GL_FALSE)) )
        
        WT_GL_ASSERT( glDrawElements(GLenum(GL_TRIANGLES), GLsizei(cubeIndices.count), GLenum(GL_UNSIGNED_SHORT), cubeIndices) )
        
        WT_GL_ASSERT( glColorMask(GLboolean(GL_TRUE), GLboolean(GL_TRUE), GLboolean(GL_TRUE), GLboolean(GL_TRUE)) )
    }
}
