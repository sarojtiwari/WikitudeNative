//
//  WTInstantTrackingCoordinateConversionHandler.h
//  WikitudeNativeSDK
//
//  Created by Daniel Guttenberg on 28/07/17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#import "WTPoint3D.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * @brief Block typedef for the completion handler of `convertScreenCoordinate:toPointCloudCoordinateOnQueue:completion`
 */
typedef void(^WTInstantTrackingCoordinateConversionHandler)(BOOL success, WTPoint3D * __nullable pointCloudCoordinate);

/**
 * @brief Block typedef for the completion handler of `convertScreenCoordinatetoPointCloudCoordinate:success:error:`
 */
typedef void(^WTInstantTrackingCoordinateConversionSuccessHandler)(WTPoint3D pointCloudCoordinate);

/**
 * @brief Block typedef for the completion handler of `convertScreenCoordinatetoPointCloudCoordinate:success:error:`
 * @param error - Error message in human readable form
 */
typedef void(^WTInstantTrackingCoordinateConversionErrorHandler)(NSError * error);

NS_ASSUME_NONNULL_END
