//
//  WikitudeNativeSDK.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 18/04/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for WikitudeNativeSDK.
FOUNDATION_EXPORT double WikitudeNativeSDKVersionNumber;

//! Project version string for WikitudeNativeSDK.
FOUNDATION_EXPORT const unsigned char WikitudeNativeSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <WikitudeNativeSDK/PublicHeader.h>
#import <WikitudeNativeSDK/WTWikitudeNativeSDK.h>

#import <WikitudeNativeSDK/WTSDKBuildInformation.h>

#import <WikitudeNativeSDK/WTAuthorizationRequestManager.h>
#import <WikitudeNativeSDK/WTNativeSDKStartupConfiguration.h>
//#import <WikitudeNativeSDK/WTExternalCMMotionManagerDataAccessMode.h>

#import <WikitudeNativeSDK/WTCaptureDeviceManager.h>

#import <WikitudeNativeSDK/WTEAGLView.h>
#import <WikitudeNativeSDK/WTMetalView.h>

#import <WikitudeNativeSDK/WTTrackerManager.h>

#import <WikitudeNativeSDK/WTTarget.h>

#import <WikitudeNativeSDK/WTTargetCollectionResource.h>

#import <WikitudeNativeSDK/WTCloudRecognitionService.h>
#import <WikitudeNativeSDK/WTCloudRecognitionServiceConfiguration.h>
#import <WikitudeNativeSDK/WTCloudRecognitionServiceResponse.h>

#import <WikitudeNativeSDK/WTImageTracker.h>
#import <WikitudeNativeSDK/WTImageTrackerDelegate.h>
#import <WikitudeNativeSDK/WTImageTrackerConfiguration.h>
#import <WikitudeNativeSDK/WTImageTarget.h>

#import <WikitudeNativeSDK/WTInstantTracker.h>
#import <WikitudeNativeSDK/WTInstantTarget.h>
#import <WikitudeNativeSDK/WTInstantTrackerDelegate.h>
#import <WikitudeNativeSDK/WTInstantTrackerConfiguration.h>
#import <WikitudeNativeSDK/WTPlaneDetectionConfiguration.h>
#import <WikitudeNativeSDK/WTInitializationPose.h>
#import <WikitudeNativeSDK/WTPlane.h>
#import <WikitudeNativeSDK/WTPlaneFilter.h>
#import <WikitudeNativeSDK/WTPlaneType.h>
#import <WikitudeNativeSDK/WTInstantTrackingCoordinateConversionHandler.h>
#import <WikitudeNativeSDK/WTInstantTrackingPointCloudDataProvider.h>
#import <WikitudeNativeSDK/WTCPPInstantTrackingPointCloudDataProvider.h>
#import <WikitudeNativeSDK/WTInstantTrackingSaveLoadInstantTargetHandlers.h>
#import <WikitudeNativeSDK/WTConvexPlaneHullDataProvider.h>

#import <WikitudeNativeSDK/WTObjectTracker.h>
#import <WikitudeNativeSDK/WTObjectTrackerDelegate.h>
#import <WikitudeNativeSDK/WTObjectTrackerConfiguration.h>
#import <WikitudeNativeSDK/WTObjectTarget.h>

#import <WikitudeNativeSDK/WTPoint2D.h>

#import <WikitudeNativeSDK/WTDeprecation.h>

#import <WikitudeNativeSDK/CameraFrame.hpp>
#import <WikitudeNativeSDK/CameraFrameInputPluginModule.hpp>
#import <WikitudeNativeSDK/CameraFramePlane.hpp>
#import <WikitudeNativeSDK/CameraParameters.hpp>
#import <WikitudeNativeSDK/CameraPosition.hpp>
#import <WikitudeNativeSDK/ColorSpace.hpp>
#import <WikitudeNativeSDK/CompilerAttributes.hpp>
#import <WikitudeNativeSDK/DepthDataFormat.hpp>
#import <WikitudeNativeSDK/DeviceMotionInputPluginModule.hpp>
#import <WikitudeNativeSDK/Error.hpp>
#import <WikitudeNativeSDK/ErrorHandling.hpp>
#import <WikitudeNativeSDK/Geometry.hpp>
#import <WikitudeNativeSDK/ImageTarget.hpp>
#import <WikitudeNativeSDK/ImageTargetType.hpp>
#import <WikitudeNativeSDK/CameraFocusMode.hpp>
#import <WikitudeNativeSDK/ImageTrackingPluginModule.hpp>
#import <WikitudeNativeSDK/InstantTarget.hpp>
#import <WikitudeNativeSDK/InstantTrackingPluginModule.hpp>
#import <WikitudeNativeSDK/InstantTrackingState.hpp>
#import <WikitudeNativeSDK/InterfaceOrientation.hpp>
#import <WikitudeNativeSDK/InitializationPose.hpp>
#import <WikitudeNativeSDK/ManagedCameraFrame.hpp>
#import <WikitudeNativeSDK/Matrix4.hpp>
#import <WikitudeNativeSDK/MetalRenderingObjects.h>
#import <WikitudeNativeSDK/MetalRenderingPluginModule.hpp>
#import <WikitudeNativeSDK/OpenGLESRenderingPluginModule.hpp>
#import <WikitudeNativeSDK/ObjectTarget.hpp>
#import <WikitudeNativeSDK/ObjectTrackingPluginModule.hpp>
#import <WikitudeNativeSDK/Plane.hpp>
#import <WikitudeNativeSDK/PlaneType.hpp>
#import <WikitudeNativeSDK/PlatformCameraHandler.hpp>
#import <WikitudeNativeSDK/PlatformRuntimeHandler.hpp>
#import <WikitudeNativeSDK/PlatformTrackingHandler.hpp>
#import <WikitudeNativeSDK/Plugin.hpp>
#import <WikitudeNativeSDK/PluginModule.hpp>
#import <WikitudeNativeSDK/PluginParameterCollection.hpp>
#import <WikitudeNativeSDK/RecognizedTargetsBucket.hpp>
#import <WikitudeNativeSDK/RenderingAPI.hpp>
#import <WikitudeNativeSDK/RenderingParameters.hpp>
#import <WikitudeNativeSDK/RuntimeParameters.hpp>
#import <WikitudeNativeSDK/RenderableCameraFrame.hpp>
#import <WikitudeNativeSDK/RenderableCameraFrameBucket.hpp>
#import <WikitudeNativeSDK/RenderingPluginModule.hpp>
#import <WikitudeNativeSDK/SDKEdition.hpp>
#import <WikitudeNativeSDK/SensorEvent.hpp>
#import <WikitudeNativeSDK/State.hpp>
#import <WikitudeNativeSDK/Timestamp.hpp>
#import <WikitudeNativeSDK/TrackingParameters.hpp>
#import <WikitudeNativeSDK/TrackingPluginModule.hpp>
#import <WikitudeNativeSDK/Unit.hpp>
#import <WikitudeNativeSDK/Vector3.hpp>
#import <WikitudeNativeSDK/WTWikitudeNativeSDK+Plugins.h>
