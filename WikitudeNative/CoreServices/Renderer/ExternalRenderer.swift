//
//  ExternalRenderer.swift
//  Native Examples
//
//  Created by Max Meraner on 10/04/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import GLKit

#if ASSERT_OPENGL
    func WT_GL_ASSERT(_ __gl_code__: Any)
    {
        var __gl_code__ = ()
        var __wt_gl_error_code__: GLenum = glGetError()
        if __wt_gl_error_code__ != GL_NO_ERROR
        {
            print("OpenGL error '\(__wt_gl_error_code__)' occured at line \(#line) inside function \(#function)\n")
        }
    }
    
    func WT_GL_ASSERT_AND_RETURN<T>(_ __assign_to__: inout T, _ __gl_code__: T)
    {
        __assign_to__ = __gl_code__
        var __wt_gl_error_code__: GLenum = glGetError()
        if __wt_gl_error_code__ != GL_NO_ERROR
        {
            print("OpenGL error '\(__wt_gl_error_code__)' occured at line \(#line) inside function \(#function)\n")
        }
    }
#else
    func WT_GL_ASSERT(_ __gl_code__: Any)
    {
    }
    
    func WT_GL_ASSERT_AND_RETURN<T>(_ __assign_to__: inout T, _ __gl_code__: T)
    {
        __assign_to__ = __gl_code__
    }
#endif

typealias ExternalRenderBlock = (_ displayLink: CADisplayLink) -> Void

typealias RenderingAPI = String
let RenderingAPI_OpenGL_ES_2: RenderingAPI = "OpenGL ES 2"
let RenderingAPI_OpenGL_ES_3: RenderingAPI = "OpenGL ES 3"

class ExternalRenderer: NSObject
{
    var activeRenderingAPI:     RenderingAPI!
    
    var displayLink:            CADisplayLink?
    var eaglContext:            EAGLContext?
    
    var colorRenderBuffer:      GLuint? = 0
    var depthRenderBuffer:      GLuint? = 0
    var framebuffer:            GLuint? = 0
    var framebufferWidth:       GLint?  = 0
    var framebufferHeight:      GLint?  = 0
    
    var externalRenderBlock:    ExternalRenderBlock?
    var renderingAPIs:          NSOrderedSet!
    
    class func convertRenderingAPI(_ renderingAPI: RenderingAPI) -> EAGLRenderingAPI
    {
        var convertedRenderingAPI: EAGLRenderingAPI = EAGLRenderingAPI.openGLES2
        
        if ( renderingAPI == RenderingAPI_OpenGL_ES_2 )
        {
            convertedRenderingAPI = EAGLRenderingAPI.openGLES2
        }
        else if ( renderingAPI == RenderingAPI_OpenGL_ES_3 )
        {
            convertedRenderingAPI = EAGLRenderingAPI.openGLES3
        }
        
        return convertedRenderingAPI
    }
    
    // MARK: - Public Methods
    func setupRendering(with eaglLayer: CAEAGLLayer, OpenGLESRenderingAPIs renderingAPIs:NSOrderedSet)
    {
        if ( nil == self.eaglContext )
        {
            self.renderingAPIs = renderingAPIs
            self.eaglContext = createContext()
            if ( nil != self.eaglContext )
            {
                assureCurrentContext()
                
                WT_GL_ASSERT( glGenFramebuffers(1, &self.framebuffer!) )
                WT_GL_ASSERT( glBindFramebuffer(GLenum(GL_FRAMEBUFFER), self.framebuffer!) )
                
                WT_GL_ASSERT( glGenRenderbuffers(1, &self.colorRenderBuffer!) )
                WT_GL_ASSERT( glBindRenderbuffer(GLenum(GL_RENDERBUFFER), self.colorRenderBuffer!) )
                
                let renderbufferStorageSet: Bool = self.eaglContext!.renderbufferStorage(Int(GL_RENDERBUFFER), from: eaglLayer)
                if ( !renderbufferStorageSet )
                {
                    print("Unable to set renderbuffer storage from drawable")
                    teardownRendering()
                    return
                }
                else
                {
                    WT_GL_ASSERT( glFramebufferRenderbuffer(GLenum(GL_FRAMEBUFFER), GLenum(GL_COLOR_ATTACHMENT0), GLenum(GL_RENDERBUFFER), self.colorRenderBuffer!) )
                    
                    WT_GL_ASSERT( glGetRenderbufferParameteriv(GLenum(GL_RENDERBUFFER), GLenum(GL_RENDERBUFFER_WIDTH), &self.framebufferWidth!) )
                    WT_GL_ASSERT( glGetRenderbufferParameteriv(GLenum(GL_RENDERBUFFER), GLenum(GL_RENDERBUFFER_HEIGHT), &self.framebufferHeight!) )
                    
                    WT_GL_ASSERT( glGenRenderbuffers(1, &self.depthRenderBuffer!) )
                    WT_GL_ASSERT( glBindRenderbuffer(GLenum(GL_RENDERBUFFER), self.depthRenderBuffer!) )
                    WT_GL_ASSERT( glRenderbufferStorage(GLenum(GL_RENDERBUFFER), GLenum(GL_DEPTH_COMPONENT16), self.framebufferWidth!, self.framebufferHeight!) )
                    WT_GL_ASSERT( glFramebufferRenderbuffer(GLenum(GL_FRAMEBUFFER), GLenum(GL_DEPTH_ATTACHMENT), GLenum(GL_RENDERBUFFER), self.depthRenderBuffer!) )
                    
                    let status: GLenum = glCheckFramebufferStatus(GLenum(GL_FRAMEBUFFER))
                    if ( GLenum(GL_FRAMEBUFFER_COMPLETE) != status )
                    {
                        print("Incomplete framebuffer after creation and setup: \(status)")
                        teardownRendering()
                        return
                    }
                    
                    WT_GL_ASSERT( glViewport(0, 0, self.framebufferWidth!, self.framebufferHeight!) )
                }
            }
            else
            {
                print("ERROR: The current device does not support any of the given OpenGL ES APIs: \(String(describing: self.renderingAPIs))")
            }
        }
    }
    
    func startRenderLoop(with renderBlock: ExternalRenderBlock?)
    {
        assert(renderBlock != nil, "renderBlock has nil value")
        self.externalRenderBlock = renderBlock!
        
        /* if a display link is already created, destroy it so that not two display links are activated. */
        if ( nil != self.displayLink )
        {
            stopRenderLoop()
        }
        
        self.displayLink = CADisplayLink.init(target: self, selector: #selector(self.render(with:)))
        self.displayLink!.add(to: RunLoop.current, forMode: RunLoop.Mode.default)
    }
    
    @objc func render(with displayLink: CADisplayLink)
    {
        WT_GL_ASSERT( glClearColor(0.0, 0.0, 0.0, 1.0) )
        WT_GL_ASSERT( glClear(GLbitfield(GL_COLOR_BUFFER_BIT)) )
        
        EAGLContext.setCurrent(self.eaglContext)
        
        self.externalRenderBlock!(displayLink)
        
        WT_GL_ASSERT( glEnable(GLenum(GL_DEPTH_TEST)) )
        self.eaglContext!.presentRenderbuffer(Int(self.colorRenderBuffer!))
        EAGLContext.setCurrent(nil)
    }
    
    func bindBuffer()
    {
        EAGLContext.setCurrent(self.eaglContext)
        
        WT_GL_ASSERT( glDisable(GLenum(GL_DEPTH_TEST)) )
        WT_GL_ASSERT( glBindFramebuffer(GLenum(GL_FRAMEBUFFER), self.framebuffer!) )
        WT_GL_ASSERT( glBindRenderbuffer(GLenum(GL_RENDERBUFFER), self.colorRenderBuffer!) )
    }
    
    func stopRenderLoop()
    {
        self.displayLink!.invalidate()
        self.displayLink = nil
    }
    
    func teardownRendering()
    {
        self.externalRenderBlock = nil
        
        if ( nil != self.colorRenderBuffer )
        {
            WT_GL_ASSERT( glDeleteRenderbuffers(1, &self.colorRenderBuffer!) )
        }
        
        if ( nil != self.framebuffer )
        {
            WT_GL_ASSERT( glDeleteFramebuffers(1, &self.framebuffer!) )
        }
        
        if ( nil != self.eaglContext )
        {
            self.eaglContext!.renderbufferStorage(Int(GL_RENDERBUFFER), from: nil)
            self.eaglContext = nil
        }
    }
    
    func internalContext() -> EAGLContext?
    {
        return self.eaglContext
    }
    
    // MARK: - Private Methods
    private func createContext() -> EAGLContext?
    {
        var createdContext: EAGLContext? = nil
        
        for renderingAPI in self.renderingAPIs
        {
            if let context: EAGLContext = EAGLContext.init(api: ExternalRenderer.convertRenderingAPI(renderingAPI as! RenderingAPI))
            {
                createdContext = context
                self.activeRenderingAPI = (renderingAPI as! RenderingAPI)
                break
            }
        }
        
        return createdContext
    }
    
    private func assureCurrentContext()
    {
        if ( EAGLContext.current() != self.eaglContext )
        {
            let appliedCurrentContext: Bool = EAGLContext.setCurrent(self.eaglContext!)
            if ( !appliedCurrentContext )
            {
                print("Unable to set current context")
            }
        }
    }
}
