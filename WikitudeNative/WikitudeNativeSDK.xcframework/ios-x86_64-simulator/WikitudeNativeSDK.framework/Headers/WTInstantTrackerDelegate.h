//
//  WTInstantTrackerDelegate.h
//  WikitudeNativeSDK
//
//  Created by Daniel Guttenberg on 26.04.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTInstantTrackerDelegate_h
#define WTInstantTrackerDelegate_h

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>

#import "WTDeprecation.h"
#import "WTInstantTracker.h"

NS_ASSUME_NONNULL_BEGIN

@class WTInitializationPose;
@class WTInstantTarget;
@class WTPlane;

/**
 * @brief WTInstantTrackerDelegate provides methods that propagate information about tracker state changes.
 *
 * Tracker objects are not created by calling there init method, but through the provided factory methods of WTTrackerManager.
 *
 * @discussion Matrix pointer that are provided inside the WTInstantTarget objects are only valid in the current method scope. If they are needed at a later point in time, they have to be copied into different memory that is controlled by the Wikitude Native SDK hosting application.
 */
@protocol WTInstantTrackerDelegate <NSObject>

@required
/**
 * @brief Called whenever an initialization update is being sent by the instant tracker. The tracking data can be used to draw gravity a aligned plane or other augmentations while the tracker is in the initialization state.
 *
 * @param instantTracker The tracker object that sent the initialization update.
 * @param pose Information about the gravity aligned plane
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didChangeInitializationPose:(WTInitializationPose *)pose;

/**
 * @brief Called whenever the current scene is being tracked again.
 *
 * @param instantTracker The tracker object that tracked scene
 * @param instantTarget Information about the scene being tracked
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didTrack:(WTInstantTarget *)instantTarget;

/**
 * @brief Called whenever the current scene is lost
 *
 * @discussion All WTInstantTarget matrix pointer are set to nullptr and should not be used.
 *
 * @param instantTracker The tracker object that lost the scene.
 */
- (void)instantTrackerDidStopTracking:(WTInstantTracker *)instantTracker;

@optional
/**
 * @brief Called whenever a tracker starts tracking the scene for the first time or after it was lost.
 *
 * @param instantTracker The tracker object that recognized the scene
 * @param instantTarget Information about the scene being tracked
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didStartTracking:(WTInstantTarget *)instantTarget;

/**
 * @brief Called whenever a tracker starts tracking the scene for the first time or after it was lost.
 *
 * @param instantTracker The tracker object that recognized the scene
 */
- (void)instantTrackerDidStartTracking:(WTInstantTracker *)instantTracker WT_DEPRECATED_SINCE(8.0.0, "please use -instantTracker:didStartTracking: instead which will be required in the next version.");

/**
 * @brief Called whenever a tracker changes its state internally as a result of calling setActiveInstantTrackingState: on it.
 *
 * @param instantTracker The tracker object whose state changed
 * @param newState The new state of the tracker
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didChangeState:(WTInstantTrackingState)newState;

/**
 * @brief Called whenever a state change operation of the instant tracker fails.
 *
 * @param instantTracker The tracker object that failed to perform the state change.
 * @param failedState The state that could not be changed to.
 * @param error The error object corresponding to the failure reason.
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didFailStateChange:(WTInstantTrackingState)failedState withError:(NSError *)error;

/**
 * @brief Called whenever a state change operation of the instant tracker fails.
 *
 * @param instantTracker The tracker object that failed to perform the state change.
 * @param failedState The state that could not be changed to.
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didFailStateChange:(WTInstantTrackingState)failedState WT_DEPRECATED_SINCE(8.3.0, "please use -instantTracker:didFailStateChange:withError:");

/**
 * @brief Called whenever a plane is recognized.
 *
 * @param instantTracker The tracker object that recognized the plane.
 * @param plane The plane object recognized.
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didRecognizePlane:(WTPlane *)plane;
/**
 * @brief Called whenever a plane is tracked.
 *
 * @param instantTracker The tracker object that tracked the plane.
 * @param plane The plane object tracked.
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didTrackPlane:(WTPlane *)plane;
/**
 * @brief Called whenever a plane is lost.
 *
 * @param instantTracker The tracker object that lost the plane.
 * @param plane The plane object lost.
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didLosePlane:(WTPlane *)plane;

/**
 * @brief Called whenever an operation of the instant tracker fails. An error code as well as a message that indicate the failure reason are supplied.
 *
 * @param instantTracker The tracker object that failed to perform the operation.
 * @param error The error object corresponding to the failure reason.
 */
- (void)instantTracker:(WTInstantTracker *)instantTracker didFailWithError:(NSError *)error;

@end

NS_ASSUME_NONNULL_END

#endif /* WTInstantTrackerDelegate_h */
