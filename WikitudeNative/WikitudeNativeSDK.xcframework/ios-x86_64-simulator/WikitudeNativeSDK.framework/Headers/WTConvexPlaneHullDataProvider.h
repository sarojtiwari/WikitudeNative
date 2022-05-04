//
//  WTConvexPlaneHullDataProvider.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 27.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/** @typedef WTDefaultConvexPlaneHullRequestCompletionHandler Request completion handler for WTDefaultConvexPlaneHullDataProvider. */
typedef void(^WTDefaultConvexPlaneHullRequestCompletionHandler)(NSArray<NSValue *> *convexHull);

/**
 * @brief WTConvexPlaneHullDataProvider represents an object that provides the convex plane hull's data.
 */
@interface WTConvexPlaneHullDataProvider : NSObject

@end

/**
 * @brief WTDefaultConvexPlaneHullDataProvider is the default implementation of WTConvexPlaneHullDataProvider.
 */
@interface WTDefaultConvexPlaneHullDataProvider : WTConvexPlaneHullDataProvider

/** Blocks calls to default init */
- (instancetype)init NS_UNAVAILABLE;

/** Blocks calls to new */
+ (instancetype)new NS_UNAVAILABLE;

/**
 * @brief Completion handler.
 *
 * @param completionHandler The block called once the convex hull data has been determined.
 */
+ (instancetype)convexHullDataProviderWithCompletionHandler:(WTDefaultConvexPlaneHullRequestCompletionHandler)completionHandler;

@end

NS_ASSUME_NONNULL_END
