//
//  WTObjectTrackerDelegate.h
//  WikitudeNativeSDK
//
//  Created by Daniel Guttenberg on 25.04.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTObjectTrackerDelegate_h
#define WTObjectTrackerDelegate_h

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>

#import "WTExtendedTrackingQuality.h"

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@class WTObjectTracker;
@class WTObjectTarget;

/**
 * @Brief WTOjectTrackerDelegate provides methods that propagate information about tracker state changes.
 *
 * Tracker objects are not created by calling their init method, but through the provided factory methods of WTTrackerManager.
 *
 * @discussion Matrix pointer that are provided inside the WTObjectTarget objects are only valid in the current method scope. If they are needed at a later point in time, they have to be copied into different memory that is controlled by the Wikitude Native SDK hosting application.
 */
@protocol WTObjectTrackerDelegate <NSObject>

@required
/**
 * @Brief Called whenever a tracker recognizes a new object target that was previously unknown.
 *
 * @discussion All WTObjectTarget matrix pointer are set to nullptr and should not be used.
 *
 * @param objectTracker The tracker object that recognized the new object target
 * @param recognizedObject The object target that was recognised.
 */
- (void)objectTracker:(WTObjectTracker *)objectTracker didRecognizeObject:(WTObjectTarget *)recognizedObject;

/**
 * @brief Called whenever a previously known object target was tracked again.
 *
 * @param objectTracker The tracker object that tracked the object target
 * @param trackedObject The object target tat was tracked again
 */
- (void)objectTracker:(WTObjectTracker *)objectTracker didTrackObject:(WTObjectTarget *)trackedObject;

/**
 * @brief Called whenever a previously know object target is not found anymore in the current camera frame.
 *
 * @discussion All WTObjectTarget matrix pointer are set to nullptr and should not be used.
 *
 * @param objectTracker The tracker object that lost the object target.
 * @param lostObject The object target that was lost
 */
- (void)objectTracker:(WTObjectTracker *)objectTracker didLoseObject:(WTObjectTarget *)lostObject;

@optional
/**
 * @brief Called when an object tracker was successfully initialized.
 *
 * @param objectTracker The object tracker that was initialized
 */
- (void)objectTrackerDidLoadTargets:(WTObjectTracker *)objectTracker;

/**
 * @brief Called whenever an object tracker could not be initialized.
 *
 * @param objectTracker The object tracker that could not be initialized
 * @param error A NSError object that contains more information about why the object tracker could not be initialized
 */
- (void)objectTracker:(WTObjectTracker *)objectTracker didFailToLoadTargets:(NSError *)error;

/**
 * @brief Called whenever a tracker is marked to be extended and the extended tracking quality changes.
 *
 * During a tracking session, the extended tracking quality might get better or worse, depending on the scene that is captured.
 *
 * @discussion This method is also called when extended tracking processed the first frame, meaning that oldTrackingQuality is then set to a non WTExtendedTrackingQuality value.
 *
 * @param objectTracker The tracker object that changed the extended tracking quality
 * @param extendedTarget The name of the image target that changed the extended tracking quality
 * @param oldTrackingQuality The previously extended tracking quality
 * @param newTrackingQuality The extended tracking quality that is now reached
 */
- (void)objectTracker:(WTObjectTracker *)objectTracker didUpdateExtendedTrackingQualityForTarget:(NSString *)extendedTarget fromQuality:(WTExtendedTrackingQuality)oldTrackingQuality toQuality:(WTExtendedTrackingQuality)newTrackingQuality;

@end

NS_ASSUME_NONNULL_END

#endif /* WTObjectTrackerDelegate_h */
