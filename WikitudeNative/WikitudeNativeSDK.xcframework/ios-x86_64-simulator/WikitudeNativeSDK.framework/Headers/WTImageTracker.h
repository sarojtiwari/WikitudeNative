//
//  WTImageTracker.h
//  WikitudeNativeSDK
//
//  Created by Alexandru Florea on 21/10/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef WTImageTracker_h
#define WTImageTracker_h

#import <Foundation/NSObject.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>

#import "WTDeprecation.h"
#import "WTImageTrackerDelegate.h"


NS_ASSUME_NONNULL_BEGIN

@class WTImageTarget;
@class WTTrackingInfo;
@class WTImageTracker;
@class WTImageTrackerConfiguration;

/**
 * @brief Represents a tracker that was initialized with a WTTargetCollectionResource or a WTCloudRecognitionService. It is intended to track images only.
 */
@interface WTImageTracker : NSObject

/**
 * @brief Whether the tracker is enabled.
 */
@property (nonatomic, readonly) BOOL                        enabled;


/**
 * @brief Use this method to define which targets should be extended after the image tracker was created.
 *
 * @discussion Please note that calling this method will replace all extended target definitions that were set before (also the ones from the image tracker configuration).
 *
 * @param extendedTargets An array of strings containing the names of targets that should be treated as extended targets.
 */
- (void)setExtendedTargets:(NSArray<NSString *> *)extendedTargets;

/**
 * @brief Stops any extended tracking session if started.
 *
 * @discussion After stopping an extended tracking session, the tracker will look again for a target image and resume extended tracking when it finds one.
 */
- (void)stopExtendedTracking;

/**
 * @brief Returns true if the image tracker is configured to run in extended tracking mode.
 */
- (BOOL)isExtendedTrackingActive;

/**
 * @breif Use this method to change the frequency of distance changed callbacks from the WTImageTargetDelegate
 *
 * Based on the value given, distance changed callbacks are called more or less frequently
 *
 * @param distanceChangedThreshold The threshold in millimeter that should be used.
 */
- (void)setDistanceChangedThreshold:(unsigned int)distanceChangedThreshold;

@end


NS_ASSUME_NONNULL_END

#endif /* WTImageTracker_h */
