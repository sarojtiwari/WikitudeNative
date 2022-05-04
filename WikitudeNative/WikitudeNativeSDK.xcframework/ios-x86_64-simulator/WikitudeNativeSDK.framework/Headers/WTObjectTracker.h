//
//  WTObjectTracker.h
//  WikitudeNativeSDK
//
//  Created by Alexandru Florea on 03/11/16.
//  Copyright © 2016 Wikitude. All rights reserved.
//

#ifndef WTObjectTracker_h
#define WTObjectTracker_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * @brief Represents a tracker that was initialized with a WTTargetCollectionResource. It is intended to track objects only.
 */
@interface WTObjectTracker : NSObject

/**
 * @brief Whether the tracker is enabled.
 */
@property (nonatomic, readonly) BOOL                        enabled;

/**
* @brief Use this method to define which targets should be extended after the object tracker was created.
*
* @discussion Please note that calling this method will replace all extended target definitions that were set before (also the ones from the object tracker configuration).
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

@end

NS_ASSUME_NONNULL_END

#endif /* WTObjectTracker_h */
