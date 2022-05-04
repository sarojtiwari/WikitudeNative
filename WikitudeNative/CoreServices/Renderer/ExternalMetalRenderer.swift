//
//  ExternalMetalRenderer.swift
//  Native Examples
//
//  Created by Max Meraner on 06/06/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import Metal
import UIKit
import WikitudeNativeSDK

class ExternalMetalRenderer
{
    var displayLink:                CADisplayLink!
    var mtlDevice:                  MTLDevice!
    var mtlCommandQueue:            MTLCommandQueue!
    var metalLayer:                 CAMetalLayer!
    var currentFrameDrawable:       CAMetalDrawable!
    var mtlRenderCommandEncoder:    MTLRenderCommandEncoder!
    
    var externalRenderBlock:        ExternalRenderBlock!
    
    // MARK: - Public Methods
    func setupRendering(with metalLayer: CAMetalLayer)
    {
        self.mtlCommandQueue = mtlDevice.makeCommandQueue()

        self.metalLayer = metalLayer
        self.metalLayer.device = self.mtlDevice
        self.metalLayer.pixelFormat = MTLPixelFormat.bgra8Unorm
        self.metalLayer.framebufferOnly = true
    }
    
    func startRenderLoop(with renderBlock: ExternalRenderBlock?)
    {
        assert(nil != renderBlock, "renderBlock has nil value")
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
        let mtlCommandBuffer = self.mtlCommandQueue.makeCommandBuffer()
        
        self.currentFrameDrawable = self.metalLayer.nextDrawable()
        
        let mtlRenderPassDescriptor = MTLRenderPassDescriptor.init()
        
        mtlRenderPassDescriptor.colorAttachments[0].texture = self.currentFrameDrawable.texture
        mtlRenderPassDescriptor.colorAttachments[0].loadAction = MTLLoadAction.clear
        mtlRenderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor.init(red: 1.0, green: 1.0, blue: 1.0, alpha: 1.0)
        mtlRenderPassDescriptor.colorAttachments[0].storeAction = MTLStoreAction.store
        
        self.mtlRenderCommandEncoder = mtlCommandBuffer!.makeRenderCommandEncoder(descriptor: mtlRenderPassDescriptor)
        
        self.externalRenderBlock(displayLink)
        
        self.mtlRenderCommandEncoder.endEncoding()
        mtlCommandBuffer!.present(self.currentFrameDrawable)
        mtlCommandBuffer!.commit()
    }
    
    func stopRenderLoop()
    {
        self.displayLink.invalidate()
        self.displayLink = nil
    }
    
    func teardownRendering()
    {
        self.externalRenderBlock = nil
        self.mtlDevice = nil
        self.mtlCommandQueue = nil
    }
    
    func device() -> MTLDevice?
    {
        if ( self.mtlDevice == nil )
        {
            self.mtlDevice = MTLCreateSystemDefaultDevice()
        }
        return self.mtlDevice
    }
    
    func commandQueue() -> MTLCommandQueue?
    {
        if ( self.mtlCommandQueue == nil )
        {
            self.mtlCommandQueue = self.device()!.makeCommandQueue()
        }
        return self.mtlCommandQueue
    }
    
    func renderCommandEncoder() -> MTLRenderCommandEncoder
    {
        return self.mtlRenderCommandEncoder
    }
}
