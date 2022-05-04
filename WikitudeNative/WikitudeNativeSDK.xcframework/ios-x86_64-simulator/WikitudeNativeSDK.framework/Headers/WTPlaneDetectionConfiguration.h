//
//  WTPlaneDetectionConfiguration.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 27.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WTPlaneFilter.h"


NS_ASSUME_NONNULL_BEGIN
/**
 * @brief WTPlaneDetectionConfiguration is used to define how plane detection should run.
 */
@interface WTPlaneDetectionConfiguration : NSObject
/** Defines orientation of planes to consider */
@property (nonatomic, assign) WTPlaneFilter     planeFilter;
/** Enables/disables the plane's convex hull */
@property (nonatomic, assign) BOOL              enableConvexHull;

@end

NS_ASSUME_NONNULL_END
