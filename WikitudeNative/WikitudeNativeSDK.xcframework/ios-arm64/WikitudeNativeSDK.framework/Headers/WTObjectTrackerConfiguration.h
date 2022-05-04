//
//  WTObjectTrackerConfiguration.h
//  WikitudeNativeSDK
//
//  Created by Daniel Guttenberg on 25.04.2018.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTObjectTrackerConfiguration_h
#define WTObjectTrackerConfiguration_h

#import <Foundation/Foundation.h>

#import "WTWikitudeTypes.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * @brief WTImageTrackerConfiguration represents additional values that can be used to configure how an image tracker behaves.
 */
@interface WTObjectTrackerConfiguration : NSObject

/**
 * @brief An array of NSString objects that represent which targets of the .wtc file should be treated as extended targets.
 *
 * @discussion The extended targets array is usually set through the client tracker creation factory method.
 */
@property (nonatomic, strong) NSArray                               *extendedTargets;

/** @brief Use this property to specify the efficiency mode of the tracker.
 *
 * Please refer to the TrackerEfficiencyMode documentation for more details.
 */
@property (nonatomic, assign) WTTrackerEfficiencyMode               trackerEfficiencyMode;

@end

NS_ASSUME_NONNULL_END

#endif /* WTObjectTrackerConfiguration_h */
