//
//  WTPlane.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 26.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>
#include <simd/packed.h>

#import "WTDeprecation.h"
#import "WTPlaneType.h"
#import "WTExtent.h"
#import "WTConvexPlaneHullDataProvider.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * @brief WTPlane represents a 3D plane object.
 */
@interface WTPlane : NSObject

/**
 * @brief A 4x4 modelView matrix that represents translation and rotation of a image target.
 *
 * Might be set to NULL
 *
 * @return modelView A 4x4 matrix that defines translation and rotation of a image target in a 3d space.
 */
@property (nonatomic, assign, readonly) const float*    matrix;

/** Unique identifier of the plane */
@property (nonatomic, assign, readonly) long            uniqueId;

/** Orientation of the plane */
@property (nonatomic, assign, readonly) WTPlaneType     type;

/** Length of the plane along the X axis */
@property (nonatomic, assign, readonly) WTExtent        extentX;

/** Length of the plane along the Y axis */
@property (nonatomic, assign, readonly) WTExtent        extentY;

/**
 * @brief Access the plane's convex hull data.
 *
 * Always check pointsCount after the method returned. In case it is 0, the array pointer pointer was not assigned to any data.
 *
 * The data pointed to by pointsArray is valid for the lifetime of the WTPlane object that returned it.
 *
 * @param pointsArray A pointer to a simd_packed_float2 array that will contain the points of the convex hull after the method returned.
 * @param pointsCount A pointer to a NSUInteger that will contain the number of points in the convex hull after the method returned.
 */
- (void)convexHullPoints:(const simd_packed_float2 *_Nullable *_Nullable)pointsArray count:(NSUInteger *)pointsCount;

/**
 * @brief Requests the plane's convex hull from the data provider.
 *
 * @param dataProvider The object that determines and provides the convex plane hull's data.
 * @deprecated use -convexHullPoints:count: instead.
 */
- (void)requestConvexHull:(WTConvexPlaneHullDataProvider *)dataProvider WT_DEPRECATED_SINCE(8.4.0, "Use -convexHullPoints:count: instead.");

@end

NS_ASSUME_NONNULL_END
