//
//  ExternalMetalView.swift
//  Native Examples
//
//  Created by Max Meraner on 31/05/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Metal
import MetalKit

class ExternalMetalView: UIView
{
    override class var layerClass: AnyClass
        {
        get
        {
            return CAMetalLayer.self
        }
    }
    
    init()
    {
        super.init(frame: CGRect.zero)
        initMetal()
    }
    
    required init?(coder: NSCoder)
    {
        super.init(coder: coder)
        initMetal()
    }
    
    override init(frame: CGRect)
    {
        super.init(frame: frame)
        initMetal()
    }
    
    func initMetal()
    {
        let metalLayer: CAMetalLayer! = (layer as! CAMetalLayer)
        metalLayer.isOpaque = true
        metalLayer.pixelFormat = MTLPixelFormat.bgra8Unorm
        metalLayer.framebufferOnly = true

        contentScaleFactor = UIScreen.main.scale
    }
    
    // MARK: - Public Methods
    func metalLayer() -> CAMetalLayer
    {
        return (layer as! CAMetalLayer)
    }
}

