//
//  WikitudeViewController.swift
//  WikitudeNative
//
//  Created by Saroj Tiwari on 04/05/2022.
//

import Foundation
import UIKit
import WikitudeNativeSDK


class WikitudeViewController: UIViewController {
   
    
    var wikitudeSDK: WTWikitudeNativeSDK!
    var cloudRecognitionService: WTCloudRecognitionService!
    var imageTracker: WTImageTracker!
    var sharedWikitudeEAGLCameraContext:EAGLContext!
    
    var wikitudeUpdateHandler: WTWikitudeOpenGLESUpdateHandler?
    var wikitudeDrawHandler: WTWikitudeOpenGLESDrawHandler?
    var isTracking: Bool = false
    
    var renderer: ExternalRenderer!
    var renderableRectangle:StrokedRectangle!
    
    var targetImageView: WTTargetImageView!
    var renderingAPIVersion:EAGLRenderingAPI!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        let eagleView = ExternalEAGLView()
        view.addSubview(eagleView)
        eagleView.translatesAutoresizingMaskIntoConstraints = false
        eagleView.frame = view.frame
        
        self.renderer = ExternalRenderer()
        self.renderableRectangle = StrokedRectangle()
        
        
        self.renderer.setupRendering(with: eagleView.eaglLayer(), OpenGLESRenderingAPIs: NSOrderedSet.init(objects: RenderingAPI_OpenGL_ES_2))
        self.renderer.startRenderLoop(with: self.renderBlock())
        
        let renderingConfiguration = WTWikitudeNativeSDK.createExternalMetalRenderingConfiguration(self)
        
        self.wikitudeSDK = WTWikitudeNativeSDK.init(renderingConfiguration: renderingConfiguration, delegate: self)
        
        self.wikitudeSDK.setLicenseKey(licenseKey)
        self.targetImageView = WTTargetImageView()
        self.view.addSubview(self.targetImageView)
        
        let imageNames: [String] = ["austria", "brazil", "france", "germany", "italy"]
        self.targetImageView.isHidden = true
        self.targetImageView.setupView(with: imageNames, topLayoutGuide: self.topLayoutGuide)
        
        initializeSDK()
    }
    
    
    func initializeSDK(){
        self.wikitudeSDK.start(nil) { runnig, error in
            if !runnig {
                print("Wikitude SDK is not runnigg \(error.localizedDescription)")
            } else {
                weak var weakSelf = self
                self.cloudRecognitionService =
                self.wikitudeSDK.trackerManager().createCloudRecognitionService(withClientToken: "1535bb751a4f65217bf361a11e548e29", groupId: "YUsJs1AQp7", targetCollectionId: "626f7c5d78eb89005c4e7cd6", completion: { running, error in
                    if (!runnig) {
                        print("Cloud Service failed to initialize \(error?.localizedDescription)")
                    } else {
                        print("Creating image tracker")
                        self.imageTracker = self.wikitudeSDK.trackerManager().createImageTracker(from: self.cloudRecognitionService, delegate: self, configuration: nil)
                        self.trackCloudImage()
                        
                    }
                })
                
            }
        }
    }
    
    // MARK: - ExternalRenderer render loop
    func renderBlock() -> ExternalRenderBlock
    {
        return { (displayLink: CADisplayLink?) -> Void in
            if ( ( nil != self.wikitudeUpdateHandler ) &&
                ( nil != self.wikitudeDrawHandler ) )
            {
                self.wikitudeUpdateHandler!()
                self.wikitudeDrawHandler!()
            }
            
            self.renderer.bindBuffer()
            
            if ( self.isTracking )
            {
                if let internalContext = self.renderer.internalContext()
                {
                    self.renderableRectangle.draw(in: internalContext)
                }
            }
        }
    }
    
    func trackCloudImage(){
        if ( nil != self.cloudRecognitionService && self.cloudRecognitionService.initialized )
        {
            self.cloudRecognitionService.recognize({[weak self] (response: WTCloudRecognitionServiceResponse?, error: Error?) in
                guard let strongSelf = self else {return}
                if ( nil != response )
                {
                    if ( response!.recognized )
                    {
                        let targetName = response!.targetInformations[WTCloudRecognitionServiceResponseKey_TargetName] as! String
                        let targetRating = response!.targetInformations[WTCloudRecognitionServiceResponseKey_TargetRating] as! Int
                        let metaData = response!.metadata as! Dictionary<String, String>
                        print("Recognized target '\(targetName)' which has a rating of '\(String(describing: targetRating))'")
                        print("Associated (custom) metadata: \(String(describing: metaData))")
                    }
                    else
                    {
                        print("No target image found in the analysed camera frame.\nKeep Calm \n\t&\nKeep Looking")
                    }
                }
                else
                {
                    print("Cloud recognition recognition failed. Reason: \(error!.localizedDescription)")
                }
            })
        }
    }
    
}




// MARK: - Wikitude SDK Delegate

extension WikitudeViewController: WTWikitudeNativeSDKDelegate, WTImageTrackerDelegate {
    // MARK: - WTImageTrackerDelegate
    func imageTracker(_ imageTracker: WTImageTracker, didRecognizeImage recognizedTarget: WTImageTarget)
    {
        print("recognized target '\(recognizedTarget.name)'")
        //self.isTracking = true
    }
    
    func imageTracker(_ imageTracker: WTImageTracker, didTrackImage trackedTarget: WTImageTarget)
    {
        debugPrint("This is the tracked image \(trackedTarget.name)")
    }
    
    func imageTracker(_ imageTracker: WTImageTracker, didLoseImage lostTarget: WTImageTarget)
    {
        print("lost target '\(lostTarget.name)'")
    }
    
    func imageTrackerDidLoadTargets(_ imageTracker: WTImageTracker)
    {
        print("Image tracker loaded")
    }
    
    func imageTracker(_ imageTracker: WTImageTracker, didFailToLoadTargets error: Error)
    {
        print("Unable to load image tracker. Reason: \(error.localizedDescription)")
    }
    
}



// MARK: - External Rendering Protocol

extension WikitudeViewController: WTExternalMetalRenderingProtocol {
    func wikitudeNativeSDK(_ wikitudeNativeSDK: WTWikitudeNativeSDK, didCreateExternalMetalDrawHandler drawHandler: @escaping WTWikitudeMetalDrawHandler) {
        //
    }
    
    
//    func wikitudeNativeSDK(_ wikitudeNativeSDK: WTWikitudeNativeSDK, didCreateExternalOpenGLESUpdateHandler updateHandler: @escaping WTWikitudeOpenGLESUpdateHandler)
//    {
//        self.wikitudeUpdateHandler = updateHandler
//    }
    
    func wikitudeNativeSDK(_ wikitudeNativeSDK: WTWikitudeNativeSDK, didCreateExternalMetalUpdateHandler drawHandler: @escaping WTWikitudeOpenGLESDrawHandler)
    {
        self.wikitudeUpdateHandler = drawHandler
    }
    
    func viewSizeForExternalRendering(in wikitudeNativeSDK: WTWikitudeNativeSDK) -> CGRect {
        return self.view.bounds
    }
    
    func metalDeviceForVideoCamera(in wikitudeNativeSDK: WTWikitudeNativeSDK) -> MTLDevice {
        return ExternalMetalRenderer().device()!
    }
    
    func metalCommandQueueForVideoCamera(in wikitudeNativeSDK: WTWikitudeNativeSDK) -> MTLCommandQueue {
        return ExternalMetalRenderer().commandQueue()!
    }

    func metalPixelFormatForVideoCamera(in wikitudeNativeSDK: WTWikitudeNativeSDK) -> MTLPixelFormat {
        return MTLPixelFormat(rawValue: 10)!
    }
    
    func eaglContextForVideoCamera(in wikitudeNativeSDK: WTWikitudeNativeSDK) -> EAGLContext
    {
        if ( nil == self.sharedWikitudeEAGLCameraContext )
        {
            if let rendererContext: EAGLContext = self.renderer.internalContext()
            {
                self.sharedWikitudeEAGLCameraContext = EAGLContext.init(api: rendererContext.api, sharegroup: rendererContext.sharegroup)
            }
        }
        return self.sharedWikitudeEAGLCameraContext
    }
    
    func eaglViewSizeForExternalRendering(in wikitudeNativeSDK: WTWikitudeNativeSDK) -> CGRect
    {
        return self.view.bounds
    }
    
    func wikitudeNativeSDK(_ wikitudeNativeSDK: WTWikitudeNativeSDK, didEncounterInternalError error: Error)
    {
        print("Internal Wikitude SDK error encountered. \(error.localizedDescription)")
    }
    
}








let licenseKey = "qhqjpJhmHFKtuB/28sO+5bJHz337b80DH1Q7h0cEzpoOCHhvdhhdPwOb1Uh8kwiGfbXjophnnQ25BOQjOCUJnKu/x7ywgckX3yQBbFCDczMU98BeMf6/mocb7DSko488DWwxO9N5Rk5QyuJLBSs/bm8bfF5deP5TB1Y10KcWDV5TYWx0ZWRfX9e6OMe3SCYRY82e2buT8i5yseO6qnygmSU4wkzDX1sxleQPitqmQwGfwLIzcz1q9zePQKG3I2pdBt7pdb19iZS6H46PgachsXpX6s3xHaCDMGJ6vAXWKvr+7kqVCAmC0Q5z7PhI1lxpOUAd7lxQj+HwUYdC9GXjL+ZfCLJkPvipXqLZ5CwfYSKrDEm+0WeI9hqb4XXiBbVR6N18eK9nirov5hAo7uiqhcBG528OdyWn2UylXcPsW/6DqwTZxiVC9GW9MP9+dwtKYXsmXdoP6KhqId6uFRltU/TIAbmttl7l8F1L9pZb0IIJHGvEmwHx1NlDx2UxNOPLiXdMSHLw/0TD+6NJkG4ksculS8rwsJSmVMXu7JWYWFxIj4JhN8Kwmr+9XaANbdijajsnXXbwh/gWeyo5gVdJ54a3vGAHZm/A7/6KpoIJ7e8PDzbTLpfXnRzc5EVaP1g/bGMyedeIfkFp2+Xly4VhqRECndWlYz6ZeCqMTDDbS/dGcqBAohLASxdPn1LYsuCPqAzUvVA9WjC+malVW46DOSJ4r5RirFeJNOA6EBkJRd1WTGBEMeK9/o3Hax2fYnI3lWqSLjmoZI4axm1lRVlFpevVRUOVzrgOag8sqLBEOWmb0Mp03LUNyt7SDunGSARaBik8mr9yiU00UFdKl776eWEdK1nnKylSdDZcSirBfSg="
