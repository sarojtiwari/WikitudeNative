//
//  WTInstantTrackingSaveLoadSceneHandlers.h
//  WikitudeNativeSDK
//
//  Created by Daniel Guttenberg on 30/04/18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#import <Foundation/NSString.h>
#import <Foundation/NSError.h>

#import "WTInstantTargetRestorationConfiguration.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * @brief Block typedef that is called when an instant target is saved.
 */
typedef void(^WTSaveCurrentInstantTargetSuccessHandler)(NSString* instantTargetPath);

/**
 * @brief Block typedef that is called when an error occurs when trying to save an instant target.
 */
typedef void(^WTSaveCurrentInstantTargetErrorHandler)(NSError *error);

/**
 * @brief Block typedef that is called to convert a configuration after a target is reloaded.
 */
typedef void(^WTInstantTrackingTargetRestorationConfigurationHandler)(WTInstantTargetRestorationConfiguration *configuration);

/**
 * @brief Block typedef that is called when an instant target is loaded.
 */
typedef void(^WTLoadInstantTargetSuccessHandler)(NSString *instantTargetPath);

/**
 * @brief Block typedef that is called when an error occurs when trying to load an instant target.
 */
typedef void(^WTLoadInstantTargetErrorHandler)(NSError *error);

NS_ASSUME_NONNULL_END
