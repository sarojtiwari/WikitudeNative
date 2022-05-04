//
//  WTImageTrackerDelegate.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 22.04.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTImageTrackerDelegate_h
#define WTImageTrackerDelegate_h

#import <Foundation/NSObject.h>
#import <Foundation/NSError.h>

#import "WTExtendedTrackingQuality.h"


NS_ASSUME_NONNULL_BEGIN

@class WTImageTarget;
@class WTTrackingInfo;
@class WTImageTracker;

/**
 * @Brief WTImageTrackerDelegate provides methods that propagate information about tracker state changes.
 *
 * Tracker objects are not created by calling their init method, but through the provided factory methods of WTTrackerManager.
 *
 * @discussion Matrix pointer that are provided inside the WTImageTarget objects are only valid in the current method scope. If they are needed at a later point in time, they have to be copied into different memory that is controlled by the Wikitude Native SDK hosting application.
 */
@protocol WTImageTrackerDelegate <NSObject>

@required
/**
 * @Brief Called whenever a tracker recognizes a new image target that was previously unknown.
 *
 * @discussion All WTImageTarget matrix pointer are set to nullptr and should not be used.
 *
 * @param imageTracker The tracker object that recognized the new image target
 * @param recognizedTarget The image target that was recognised.
 */
- (void)imageTracker:(WTImageTracker *)imageTracker didRecognizeImage:(WTImageTarget *)recognizedTarget;

/**
 * @brief Called whenever a previously known image target was tracked again.
 *
 * @param imageTracker The tracker object that tracked the image target
 * @param trackedTarget The image target tat was tracked again
 */
- (void)imageTracker:(WTImageTracker *)imageTracker didTrackImage:(WTImageTarget *)trackedTarget;

/**
 * @brief Called whenever a previously know image target is not found anymore in the current camera frame.
 *
 * @discussion All WTImageTarget matrix pointer are set to nullptr and should not be used.
 *
 * @param imageTracker The tracker object that lost the image target.
 * @param lostTarget The image target that was lost
 */
- (void)imageTracker:(WTImageTracker *)imageTracker didLoseImage:(WTImageTarget *)lostTarget;

@optional
/**
 * @brief Called when an image tracker was successfully initialized.
 *
 * @param imageTracker The image tracker that was initialized
 */
- (void)imageTrackerDidLoadTargets:(WTImageTracker *)imageTracker;

/**
 * @brief Called whenever an image tracker could not be initialized.
 *
 * @param imageTracker The image tracker that could not be initialized
 * @param error A NSError object that contains more information about why the image tracker could not be initialized
 */
- (void)imageTracker:(WTImageTracker *)imageTracker didFailToLoadTargets:(NSError *)error;


/**
 * @brief Called whenever a tracker is marked to be extended and the extended tracking quality changes.
 *
 * During a tracking session, the extended tracking quality might get better or worse, depending on the scene that is captured.
 *
 * @discussion This method is also called when extended tracking processed the first frame, meaning that oldTrackingQuality is then set to a non WTExtendedTrackingQuality value.
 *
 * @param imageTracker The tracker object that changed the extended tracking quality
 * @param extendedTarget The name of the image target that changed the extended tracking quality
 * @param oldTrackingQuality The previously extended tracking quality
 * @param newTrackingQuality The extended tracking quality that is now reached
 */
- (void)imageTracker:(WTImageTracker *)imageTracker didUpdateExtendedTrackingQualityForTarget:(NSString *)extendedTarget fromQuality:(WTExtendedTrackingQuality)oldTrackingQuality toQuality:(WTExtendedTrackingQuality)newTrackingQuality;

@end

NS_ASSUME_NONNULL_END

#endif /* WTImageTrackerDelegate_h */
