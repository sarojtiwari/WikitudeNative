//
//  WTInstantTracker.h
//  WikitudeNativeSDK
//
//  Created by Alexandru Florea on 17/11/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef WTInstantTracker_h
#define WTInstantTracker_h

#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

#import "WTDeprecation.h"
#import "WTInstantTrackingCoordinateConversionHandler.h"
#import "WTInstantTrackingPointCloudDataProvider.h"
#import "WTInstantTrackingSaveLoadInstantTargetHandlers.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * Assign WTInstantTrackingPlaneOrientationHorizontal to the tracking plane orientation to align it horizontally. It has a value of 0.
 */
FOUNDATION_EXPORT float const WTInstantTrackingPlaneOrientationHorizontal;

/**
 * Assign WTInstantTrackingPlaneOrientationVertical to the tracking plane orientation to align it vertically. It has a value of 90.
 */
FOUNDATION_EXPORT float const WTInstantTrackingPlaneOrientationVertical;

/**
 * WTInstantTrackingState indicates the current state in which an instant tracker is.
 */
typedef NS_ENUM(NSInteger, WTInstantTrackingState) {
    /**
     * WTInstantTarckerInitializing indicates that the instant tracker is in initialization state, which allows the origin of the tracking scene to be set, as well as the device height above ground.
     */
    WTInstantTrackerInitializing = 0,
    /**
     * WTInstantTrackerTracking indicates that the instant tracker is in tracking state, which means that the current scene is being tracker and augmentations can be placed.
     */
    WTInstantTrackerTracking = 1
};

@class WTTargetCollectionResource;

/**
 * @brief Represents a tracker that can instantly start tracking a scene with any markers.
 * 
 * @discussion Instant trackers start in initializing state, during which the origin of the tracked scene can be set by rotating the device. Displaying a gravity aligned plane or target in the center of the screen can help users through this process. After this was set, the instant tracker can instantly transition to the tracking state, during which the actual tracking of the scene takes place.
 */
@interface WTInstantTracker : NSObject 

/**
 * @brief Whether the tracker is enabled.
 */
@property (nonatomic, readonly) BOOL                        enabled;

/**
 * @brief Changes the tracking state of the instant tracker
 *
 * @discussion The tracking state is not changed immediately, and the didChangeState method can be used to get notified of exactly when that happens.
 *
 * @param state The new state to which the instant tracker should switch to
 */
- (void)setActiveInstantTrackingState:(WTInstantTrackingState)state;

/**
 * @brief Allows changing the estimated height at which the device is currently above the ground.
 *
 * @discussion Setting this to an appropriate value will allow the augmentations to have a scale close to the one they would have in reality.
 *
 * @param height The estimated device height above the ground in meters
 */
- (void)setDeviceHeightAboveGround:(float)height;

/**
 * @brief Allows changing the orientation of the plane with which the instant tracking initializes
 *
 * @discussion The orientation can only be changed if the active instant tracking state is WTInstantTrackerInitializing. It can be set to all values between 360 and -360. This can enable e.g. easier tracking on walls and ceilings.
 *
 * @param trackingPlaneOrientation The orientation of the tracking plane in degrees
 */
- (void)setTrackingPlaneOrientation:(float)trackingPlaneOrientation;

/**
 * @brief use this method to perform a hit test on the point cloud coming from the instant tracker.
 *
 * When invoking this method, a block on the given operation queue is dispatched which performs the hit test operation.
 * In case there is no point at the given screen coordinate, the BOOL property in the completion handler is set to NO. Otherwise the given 3d coordinate can be used to position an augmentation at this point.
 *
 * @param screenCoordinate The screen coordinate for that a hit test should be performed
 * @param operationQueue The operation queue on which the hit test computation should be performed
 * @param completionHandler The block that should be called when the hit test computation finishes
 */
- (void)convertScreenCoordinate:(CGPoint)screenCoordinate toPointCloudCoordinateOnQueue:(NSOperationQueue *)operationQueue completion:(WTInstantTrackingCoordinateConversionHandler)completionHandler WT_DEPRECATED_SINCE(8.0.0, "Use -convertScreenCoordinatetoPointCloudCoordinate:success:error instead.");

/** @brief Use this method to perform a hit test on the point cloud coming from the instant tracker.
 *
 *  This operation is performed on a separate thread and the successHandler is called from that thread.
 *  Because this operation uses screen coordinates, please make sure that surface changed is called at least once before invoking this method.
 *
 *  @param screenCoordinate The screen coordinate for which a hit test should be performed.
 *  @param successHandler The callback that should be called when the hit test computation finishes. This will be called from another thread.
 *  @param errorHandler The callback that should be called when an error occurs.
 */

- (void)convertScreenCoordinatetoPointCloudCoordinate:(CGPoint)screenCoordinate success:(WTInstantTrackingCoordinateConversionSuccessHandler)successHandler error:(WTInstantTrackingCoordinateConversionErrorHandler)errorHandler;

/**
 * @brief use this method to get all points of the current point cloud that is managed by this instant tracker
 *
 * When invoking this method, a block on the given operation queue is dispatched which performs the point cloud retrieval.
 *
 * @param operationQueue The operation queue on which the point cloud retrieval is performed
 * @param dataProvider The data provider that should be used to provide the current point cloud.
 */
- (void)requestCurrentPointCloudOnQueue:(NSOperationQueue *)operationQueue representedThroughDataProvider:(WTInstantTrackingPointCloudDataProvider *)dataProvider WT_DEPRECATED_SINCE(8.0.0, "Use -requestCurrentPointCloudRepresentedThroughDataProvider: instead.");

/**
 * @brief use this method to get all points of the current point cloud that is managed by this instant tracker
 *
 * @param dataProvider The data provider that should be used to provide the current point cloud.
 */
- (void)requestCurrentPointCloudRepresentedThroughDataProvider:(WTInstantTrackingPointCloudDataProvider *)dataProvider;

/**
 * @brief Use this method to query whether a state change from initialization state to tracking state can be performed.
 *
 * @discussion For Wikitude's instant tracking algorithm, this function currently always returns YES because the state change is always possible. For ARKit this function performs a hit test internally to check whether the state can be switched or not. Theoretically, the state change could still be unsuccessful after this function has indicated otherwise due to a hit test position that differs and a temporal delay between the two calls. Practically, this is the best we can do and it works consistently.
 *
 * @return A BOOL value indicating the viability of a subsequent state change. YES for viable, NO for not viable.
 */
- (BOOL)canStartTracking;

/**
 * @brief Use this method to persist the currently tracked instant tracking session as a file.
 *
 * @discussion Saving the current session as an instant target happens on a background thread. In case the given directory does not exist, the error handler is called with a description and more details.
 * In case the directory exists and a file with the same name in it exists, it will be overridden.
 * The file type is .wto
 *
 * @param instantTargetDestinationURL A iOS sandbox compliant URL including a file name to which the current session should be saved to. NSFileManager can be used to get such a URL.
 * @param successHandler A completion handler that is called if the current session could be successfully stored at the given URL. This handler might be called from a background thread.
 * @param errorHandler A completion handler that is called in case the current session could not be successfully stored at the given URL. The given NSError contains more information why the operation failed.
 */
- (void)saveCurrentInstantTargetWithSceneName:(NSURL *)instantTargetDestinationURL success:(WTSaveCurrentInstantTargetSuccessHandler)successHandler error:(WTSaveCurrentInstantTargetErrorHandler)errorHandler;

/**
 * @brief Use this method to load a previously stored instant target.
 *
 * @discussion Loading an instant target happens on a background thread.
 *
 * @param targetCollectionResource The target collection resource that points to a .wto file (either on the device or a remote server). Please refer to `WTTrackerManager` `-createTargetCollectionResourceFromURL:` for more information.
 * @param restorationHandler This handler is used to provide further information on how the previously stored instant target should be restored. Please refer to the `WTInstantTargetRestorationConfiguration` class reference for more information.
 * @param successHandler A completion handler that is called once the instant target is fully restored and ready for recognition.
 * @param errorHandler A completion handler that is called in case the instant target could not be restored. The given NSError contains more information why the operation failed.
 */
- (void)loadExistingInstantTargetWithTargetCollectionResource:(WTTargetCollectionResource *)targetCollectionResource restoration:(WTInstantTrackingTargetRestorationConfigurationHandler)restorationHandler success:(WTLoadInstantTargetSuccessHandler)successHandler error:(WTLoadInstantTargetErrorHandler)errorHandler;

@end

NS_ASSUME_NONNULL_END

#endif /* WTInstantTracker_h */
