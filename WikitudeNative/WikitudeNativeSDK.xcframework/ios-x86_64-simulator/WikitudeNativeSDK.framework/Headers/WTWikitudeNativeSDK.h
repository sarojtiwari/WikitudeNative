//
//  WikitudeNativeSDK.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 18/04/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <UIKit/UIViewController.h>
#import <CoreGraphics/CGGeometry.h>
#import <AVFoundation/AVCaptureDevice.h>
#import <CoreMedia/CMTime.h>

#import "WTWikitudeTypes.h"
#import "WTOpenGLESRenderingMode.h"
#import "WTMetalRenderingMode.h"
#import "WTRenderingConfiguration.h"


NS_ASSUME_NONNULL_BEGIN

@class WTWarning;
@class WTEAGLView;
@class WTTrackerManager;
@class WTCaptureDeviceManager;
@class WTNativeSDKStartupConfiguration;
@class WTWikitudeNativeSDK;
@class WTSDKBuildInformation;

/**
 * WTWikitudeNativeSDKDelegate is used to handle information exchange between the Wikitude Native SDK and internal/external renderer as well as to inform about internal errors that occured during this conversation.
 *
 * Although all methods are marked as optional, all internal or external rendering related methods must be implemented. If not, an appropriate error is reported through the -wikitudeNativeSDK:didEncounterInternalError method.
 */
@protocol WTWikitudeNativeSDKDelegate <NSObject>
@optional

/**
 * @brief Called every time the Wikitude Native SDK encounters any internal warnings
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that encountered the internal warning
 * @param warning A warning object that contains more information about a specific warning
 */
- (void)wikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK didEncounterInternalWarning:(WTWarning *)warning;

/**
 * @brief Called every time the Wikitude Native SDK encounters any internal errors
 *
 * @param wikitudeNativeSDK The Wikitude Native SDK object that encountered the internal error
 * @param error A error object that contains more information about a specific error
 */
- (void)wikitudeNativeSDK:(WTWikitudeNativeSDK *)wikitudeNativeSDK didEncounterInternalError:(NSError *)error;

@end


/**
 * @brief WTWikitudeNativeSDK is the main entry point when using the Wikitude Native SDK.
 *
 * WTWikitudeNativeSDK coordinates how camera rendering is done (internal/external rendering), how tracker creation is handled and how capture device specific settings can be changed.
 */
@interface WTWikitudeNativeSDK : NSObject

/**
 * Returns the rendering configuration that was set when initWithRenderingConfiguration:delegate: was called
 */
@property (nonatomic, strong, readonly) WTRenderingConfiguration                *renderingConfiguration;

/**
 * Return the current SDK running State. YES if the SDK is running, false otherwise.
 */
@property (nonatomic, assign, readonly) BOOL                                    isRunning;

/**
 * @brief Returns the Wikitude Native SDK version as a formatted string.
 *
 * The format is 'major'.'minor'.'bugfix' e.g. 1.0.1
 */
+ (NSString *)sdkVersion;

/**
 * @brief Use this method to get information about the sdk build.
 *
 * @return The current available SDKBuildInformation within the SKD.
 */
+ (WTSDKBuildInformation *)SDKBuildInformation;

/** @name Accessing Device Compatibility */
/**
 * This method should be used to determine if the current device supports all features that are required.
 *
 * @param requiredFeatures Bitmask that describes wich features are used from the Wikitude SDK.
 * @param error An error object containing more information why the device is not supported if the return value is NO.
 *
 * @return true if the device supports all required features, false otherwise.
 */
+ (BOOL)isDeviceSupportingFeatures:(WTFeatures)requiredFeatures error:(NSError **)error;

/**
 * @brief Use this method to determine how the given startup configuration values are resolved on the current device.
 *
 * @discussion The configuration handler can be used to define camera related options. Based on these options, camera resolution and frame rate are resolved and returned. Please note that different camera positions can have different resolutions/frame rates. Because of that it's important to specify the captureDevicePosition in case the front cam is used.
 *
 * @param configurationHandler A block that can be used to define camera related options that are then resolved to it's size and frame rate values.
 * @param resolution On return, the size of the camera frame that can be expected at runtime
 * @param targetFrameRate On return, the frame rate at which the camera delivers new frames. In case the SDK is running with WTRenderingMode_Internal, also rendering will run with this frame rate.
 */
+ (void)resolveCaptureDeviceSettings:(nullable void (^)(WTNativeSDKStartupConfiguration *startupConfiguration))configurationHandler toSize:(CGSize *)resolution targetFrameRate:(CMTime *)targetFrameRate;

/**
 * @brief Use this method to determine which of the Rendering Configurations passed as parameters is compatible with the current device.
 *
 * @discussion Given an ordered set of Rendering Configurations, this method will return the first one that is compatible with the current device, or nil if none of the would work. If the Rendering Configurations are created manually, this method has to be called before initializing the Wikitude Native SDK, to ensure that it is compatible with the device.
 *
 * @param possibleConfigurations An NSOrderedSet of Rendering Configurations that should be checked for compatibility.
 * @return WTRenderingConfiguration The first compatible Rendering Configuration or nil.
 */
+ (WTRenderingConfiguration *)selectRenderingConfiguration:(NSOrderedSet<WTRenderingConfiguration *> *)possibleConfigurations;

/**
 * @brief Convenience method to create a pre configured OpenGL ES Rendering Configuration with internal rendering enabled.
 *
 * @discussion This method will create two Rendering Configurations with internal rendering enabled, one for OpenGL ES 3 and one for OpenGL ES 2. It will then call +selectRenderingConfiguration: and return the result.
 *
 * @param delegate The object that acts as a delegate for Internal rendering calls.
 * @return WTOpenGLESRenderingConfiguration A pre configured OpenGL ES Rendering Configuration object or nil.
 */
+ (WTOpenGLESRenderingConfiguration *)createInternalOpenGLESRenderingConfiguration:(id<WTInternalOpenGLESRenderingProtocol>)delegate;

/**
 * @brief Convenience method to create a pre configured OpenGL ES Rendering Configuration with external rendering enabled.
 *
 * @discussion This method will create two Rendering Configurations with external rendering enabled, one for OpenGL ES 3 and one for OpenGL ES 2. It will then call +selectRenderingConfiguration: and return the result.
 *
 * @param delegate The object that acts as a delegate for External rendering calls.
 * @return WTOpenGLESRenderingConfiguration A pre configured OpenGL ES Rendering Configuration object or nil.
 */
+ (WTOpenGLESRenderingConfiguration *)createExternalOpenGLESRenderingConfiguration:(id<WTExternalOpenGLESRenderingProtocol>)delegate;

/**
 * @brief Convenience method to create a pre configured Metal Rendering Configuration with internal rendering enabled.
 *
 * @discussion This method will create a Rendering Configuration with internal rendering enabled and will then call +selectRenderingConfiguration: to ensure the current device is compatible with Metal, returning the result in the end.
 *
 * @param delegate The object that acts as a delegate for Internal rendering calls.
 * @return WTMetalRenderingConfiguration A pre configured Metal Rendering Configuration object or nil.
 */
+ (WTMetalRenderingConfiguration *)createInternalMetalRenderingConfiguration:(id<WTInternalMetalRenderingProtocol>)delegate;

/**
 * @brief Convenience method to create a pre configured Metal Rendering Configuration with external rendering enabled.
 *
 * @discussion This method will create a Rendering Configuration with internal rendering enabled and will then call +selectRenderingConfiguration: to ensure the current device is compatible with Metal, return the result in the end.
 *
 * @param delegate The object that acts as a delegate for External rendering calls.
 * @return WTMetalRenderingConfiguration A pre configured Metal Rendering Configuration object or nil.
 */
+ (WTMetalRenderingConfiguration *)createExternalMetalRenderingConfiguration:(id<WTExternalMetalRenderingProtocol>)delegate;

/**
 * @brief Convenience method to create a pre configured Rendering Configuration with the highest rendering API available on the device, with internal rendering enabled.
 *
 * @discussion This method will create three Rendering Configurations with internal rendering enabled, one for Metal, one for OpenGL ES 3 and one for OpenGL ES 2. It will then call +selectRenderingConfiguration: and return the result.
 *
 * @param metalDelegate The object that acts as a delegate for Internal Metal rendering calls.
 * @param openGLESDelegate The object that acts as a delegate for Internal OpenGL ES rendering calls.
 * @return A pre configured Rendering Configuration object or nil.
 */
+ (WTRenderingConfiguration *)createInternalRenderingConfiguration:(id<WTInternalMetalRenderingProtocol>)metalDelegate openGLESDelegate:(id<WTInternalOpenGLESRenderingProtocol>)openGLESDelegate;

/**
 * @brief Convenience method to create a pre configured Rendering Configuration with the highest rendering API available on the device, with external rendering enabled.
 *
 * @discussion This method will create three Rendering Configurations with external rendering enabled, one for Metal, one for OpenGL ES 3 and one for OpenGL ES 2. It will then call +selectRenderingConfiguration: and return the result.
 *
 * @param metalDelegate The object that acts as a delegate for External Metal rendering calls.
 * @param openGLESDelegate The object that acts as a delegate for External OpenGL ES rendering calls.
 * @return A pre configured Rendering Configuration object or nil.
 */
+ (WTRenderingConfiguration *)createExternalRenderingConfiguration:(id<WTExternalMetalRenderingProtocol>)metalDelegate openGLESDelegate:(id<WTExternalOpenGLESRenderingProtocol>)openGLESDelegate;

/**
 * @brief The designated initializer to create an object of this class.
 *
 * @param renderingConfiguration The rendering configuration that should be used by the Wikitude Native SDK. If the rendering configuration was created manually, a call to +selectRenderingConfiguration: must be made before passing it. Please WTRenderingConfiguration and WTRenderingMode for more information.
 * @param delegate The object that acts as a delegate for the Wikitude native SDK object.
 * @return WTWikitudeNativeSDK An object of type WTWikitudeNativeSDK.
 */
- (instancetype)initWithRenderingConfiguration:(WTRenderingConfiguration *)renderingConfiguration delegate:(id<WTWikitudeNativeSDKDelegate>)delegate;

/**
 * @brief Provides access to a WTTrackerManager object that coordinates tracker creation
 *
 * Please refer to the WTTrackerManager documentation for more information about how to create different tracker types.
 *
 * @return A object of type WTTrackerManager that provides factory methods to create different tracker types.
 */
- (WTTrackerManager *)trackerManager;

/**
 * @brief Provides access to a WTCaptureDeviceManager if and only if the Wikitude Native SDK is currently running.
 *
 * @discussion WTCaptureDeviceManager objects can be used to change camera specific settings during Wikitude Native SDK runtime. To start the Wikitude Native SDK with non default camera parameter, please use the WTStartupConfiguration object that is passed to the startupHandler object when calling -start:completion:
 *
 * @return A valid pointer to a WTCaptureDeviceManger object if the Wikitude Native SDK is running, nil otherwise.
 */
- (nullable WTCaptureDeviceManager *)captureDeviceManager;

/**
 * @brief Enables SDK features based on the given license key.
 *
 * @discussion Depending on the license key, different types of watermarks are drawn, depending on the usage of licensed features or not. When this method is not called at all, only the camera stream is rendered but nothing else will be enabled. To try out all Wikitude Native SDK features, download a trial license from our webpage and call this method with the downloaded key.
 *
 * @param licenseKey Your developer key, provided with your licence information.
 */
- (void)setLicenseKey:(NSString *)licenseKey;

/**
 * @brief Starts Wikitude Native SDK rendering and internal updates.
 *
 * This method has to be called whenever the hosting view controllers view becomes visible or the application becomes active.
 *
 * @discussion Since some Wikitude Native SDK internal components start asynchronously, isRunning might be set to YES but an internal error is reported once a component encounters an error.
 *
 * @param startupHandler A block object that can be used to alter the Wikitude Native SDK startup behaviour
 * @param completionHandler A block object that can be used to evaluate if the Wikitude Native SDK could be started or not with the given startup configuration.
 */
- (void)start:(nullable void (^)(WTNativeSDKStartupConfiguration *configuration))startupHandler completion:(void (^)(BOOL isRunning, NSError *error))completionHandler;

/**
 * @brief Stops Wikitude Native SDK rendering and internal updates.
 *
 * This method has to be called whenever the hosting view controllers view becomes not visible anymore or the application resigns active state.
 *
 * @discussion When the hosting application resigns active state and the Wikitude Native SDK is still running, the behaviour is undefined.
 */
- (void)stop;

/**
 * @brief Call this method when the hosting view controller changes it's size.
 *
 * @discussion This method has to be called every time the rendering view, which is used by the Wikitude Native SDK, changes it's size. It might also be necessary to call this method after the Wikitude Native SDK was created and the final view layout was not set yet.
 *
 * @param size The new size of the Wikitude Native SDK rendering view.
 * @param transitionCoordinator The transition coordinator that coordinates transitioning to the new size
 */
- (void)shouldTransitionToSize:(CGSize)size withTransitionCoordinator:(nullable id<UIViewControllerTransitionCoordinator>)transitionCoordinator;

/**
 * @brief Clears all internal caches used by the SDK.
 */
- (void)clearCache;

@end

NS_ASSUME_NONNULL_END
