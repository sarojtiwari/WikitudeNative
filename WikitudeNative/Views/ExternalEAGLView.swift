//
//  ExternalEAGLView.swift
//  Native Examples
//
//  Created by Max Meraner on 07/04/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import UIKit

@objc
class ExternalEAGLView: UIView
{
    override class var layerClass: AnyClass
    {
        get
        {
            return CAEAGLLayer.self
        }
    }
    
    init()
    {
        super.init(frame: CGRect.zero)
        initOpenGLES()
    }
    
    required init?(coder: NSCoder)
    {
        super.init(coder: coder)
        initOpenGLES()
    }

    override init(frame: CGRect)
    {
        super.init(frame: frame)
        initOpenGLES()
    }
    
    func initOpenGLES()
    {
        let eaglLayer: CAEAGLLayer! = (layer as! CAEAGLLayer)
        eaglLayer.isOpaque = true
        eaglLayer.drawableProperties = [kEAGLDrawablePropertyRetainedBacking: false, kEAGLDrawablePropertyColorFormat: kEAGLColorFormatRGBA8]
        contentScaleFactor = UIScreen.main.scale
    }

    // MARK: - Public Methods
    func eaglLayer() -> CAEAGLLayer
    {
        return (layer as! CAEAGLLayer)
    }
}
