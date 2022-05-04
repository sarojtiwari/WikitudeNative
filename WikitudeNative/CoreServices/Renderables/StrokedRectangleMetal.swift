//
//  StrokedRectangleMetal.swift
//  Native Examples
//
//  Created by Max Meraner on 31/05/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

import Foundation
import MetalKit

struct Triangle {
    var position: vector_float2
    
    init(_ x: Float, _ y: Float)
    {
        position = vector_float2(x, y)
    }
}

struct VertexUniform {
    var modelView: matrix_float4x4
    var projection: matrix_float4x4
    
    init(_ modelView: matrix_float4x4, _ projection: matrix_float4x4)
    {
        self.modelView = modelView
        self.projection = projection
    }
}

struct FragmentUniform {
    var color: SIMD4<Float>
    
    init(_ color: SIMD4<Float>)
    {
        self.color = color
    }
}

class StrokedRectangleMetal
{
    public var scale:               Float!
    
    var vertices:                   MTLBuffer!
    var mtlDevice:                  MTLDevice!
    var mtlRenderPipelineState:     MTLRenderPipelineState!
    
    var projection:                 matrix_float4x4!
    var modelView:                  matrix_float4x4!
    
    var vertexUniform:              VertexUniform!
    var fragmentUniform:            FragmentUniform!
    
    init()
    {
        scale = 1
        mtlDevice = MTLCreateSystemDefaultDevice()
        setupVertices()
        setupRenderPipelineState(with: "VertexStrokedRectangle", and: "FragmentStrokedRectangle")
        
        projection = matrix_identity_float4x4
        modelView = matrix_identity_float4x4
        
        fragmentUniform = FragmentUniform(SIMD4<Float>(1.0, 0.58, 0.16, 1.0))
        vertexUniform = VertexUniform(matrix_identity_float4x4, matrix_identity_float4x4)
    }
    
    // MARK: - Public Methods
    func setProjectionMatrix(_ projectionMatrix: UnsafePointer<Float>)
    {
        memcpy(&self.projection, projectionMatrix, 16 * MemoryLayout<Float>.size)
        self.vertexUniform.projection = self.projection
    }
    
    func setModelViewMatrix(_ modelViewMatrix: UnsafePointer<Float>)
    {
        memcpy(&self.modelView, modelViewMatrix, 16 * MemoryLayout<Float>.size)
        self.vertexUniform.modelView = self.modelView
    }
    
    func setColor(_ color: UIColor)
    {
        var red: CGFloat = 0
        var green: CGFloat = 0
        var blue: CGFloat = 0
        var alpha: CGFloat = 0
        if color.getRed(&red, green: &green, blue: &blue, alpha: &alpha)
        {
            self.fragmentUniform = FragmentUniform(SIMD4<Float>(Float(red), Float(green), Float(blue), Float(alpha)))
        }
    }
    
    func releaseProgram()
    {
        self.mtlDevice = nil
        self.mtlRenderPipelineState = nil
    }
    
    func draw(with commandEncoder: MTLRenderCommandEncoder)
    {
        commandEncoder.setRenderPipelineState(self.mtlRenderPipelineState)
        
        commandEncoder.setVertexBuffer(self.vertices, offset: 0, index: 0)
        
        var scaleMatrix = matrix_identity_float4x4
        scaleMatrix.columns.0 = SIMD4<Float> ( self.scale, 0, 0, 0 )
        scaleMatrix.columns.1 = SIMD4<Float> ( 0, self.scale, 0, 0 )
        self.vertexUniform.modelView = matrix_multiply(self.vertexUniform.modelView, scaleMatrix)
        
        commandEncoder.setVertexBytes(&self.vertexUniform, length: 128, index: 1)
        
        commandEncoder.setFragmentBytes(&self.fragmentUniform, length: 16, index: 0)

        commandEncoder.drawPrimitives(type: MTLPrimitiveType.triangle, vertexStart: 0, vertexCount: 24)
    }
    
    // MARK: - Private Methods
    // MARK: Metal
    private func setupVertices()
    {
        let x: Float = 0.51
        let y: Float = 0.5
        let strokedRectangle : [Triangle] = [
            Triangle.init( -x, -x ), Triangle.init( -y, -y ), Triangle.init( -x,  x ),
            Triangle.init( -y, -y ), Triangle.init( -y,  y ), Triangle.init( -x,  x ),
            Triangle.init( -y,  y ), Triangle.init(  x,  x ), Triangle.init( -x,  x ),
            Triangle.init( -y,  y ), Triangle.init(  y,  y ), Triangle.init(  x,  x ),
            Triangle.init(  y,  y ), Triangle.init(  x, -x ), Triangle.init(  x,  x ),
            Triangle.init(  y, -y ), Triangle.init(  x, -x ), Triangle.init(  y,  y ),
            Triangle.init( -x, -x ), Triangle.init(  x, -x ), Triangle.init(  y, -y ),
            Triangle.init( -x, -x ), Triangle.init(  y, -y ), Triangle.init( -y, -y )
        ]
        
        self.vertices = self.mtlDevice.makeBuffer(bytes: strokedRectangle, length: strokedRectangle.count * MemoryLayout<Triangle>.size, options: MTLResourceOptions.cpuCacheModeWriteCombined)
    }
    
    private func setupRenderPipelineState(with vertexShader: String, and fragmentShader: String)
    {
        let renderPipelineDescriptor = MTLRenderPipelineDescriptor()
        renderPipelineDescriptor.colorAttachments[0].pixelFormat = MTLPixelFormat.bgra8Unorm
        
        let lib: MTLLibrary! = self.mtlDevice.makeDefaultLibrary()
        renderPipelineDescriptor.vertexFunction = lib.makeFunction(name: vertexShader)
        renderPipelineDescriptor.fragmentFunction = lib.makeFunction(name: fragmentShader)
        
        do
        {
            self.mtlRenderPipelineState = try self.mtlDevice.makeRenderPipelineState(descriptor: renderPipelineDescriptor)
        }
        catch let error
        {
            print("Error creating render pipeline state: \(error.localizedDescription)")
            exit(1)
        }
        
    }
}
