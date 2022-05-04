//
//  WTInstantTrackerConfiguration.h
//  WikitudeNativeSDK
//
//  Created by Max Meraner on 05/05/2017.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#ifndef WTInstantTrackerConfiguration_h
#define WTInstantTrackerConfiguration_h

#import <Foundation/Foundation.h>

#import "WTWikitudeTypes.h"


NS_ASSUME_NONNULL_BEGIN

@class WTPlaneDetectionConfiguration;

/**
 * @brief WTInstantTrackerConfiguration represents additional values that can be used to configure how an instant tracker behaves.
 */

@interface WTInstantTrackerConfiguration : NSObject

/**
 * @brief A boolean value that indicates whether SMART is to be used or not.
 *
 * @discussion When set to 'YES' the instant tracker will try to use ARKit to perform its tracking. When set to 'NO' the instant tracker will use Wikitude's instant tracking algorithms.
 *
 * @default YES
 */
@property (nonatomic, assign) BOOL                      SMARTEnabled;

/**
 * @brief Allows changing the estimated height at which the device is currently above the ground.
 *
 * @discussion Setting this to an appropriate value will allow the augmentations to have a scale close to the one they would have in reality.
 *
 * @default 1.4 (meters)
 */
@property (nonatomic, assign) float                     deviceHeightAboveGround;

/**
 * @brief An integer that represents the orientation of the tracking plane in degrees.
 *
 * @discussion The plane orientation is usually set through the instant tracker creation factory method.
 *
 * @default WTInstantTrackingPlaneOrientationHorizontal
 */
@property (nonatomic, assign) float                     trackingPlaneOrientation;

/** @brief Use this property to specify the efficiency mode of the tracker.
 *
 * Please refer to the TrackerEfficiencyMode documentation for more details.
 */
@property (nonatomic, assign) WTTrackerEfficiencyMode   trackerEfficiencyMode;

/** @brief Enables plane detection with a specific configuration.
 *
 * @param configuration The configuration that defines the behaviour of plane detection.
 */
- (void)enablePlaneDetection:(void (^)(WTPlaneDetectionConfiguration *planeDetectionConfiguration))configuration;

@end

NS_ASSUME_NONNULL_END

#endif /* WTInstantTrackerConfiguration_h */
