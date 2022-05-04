//
//  WTInstantTargetRestorationConfiguration.h
//  WikitudeNativeSDK
//
//  Created by Daniel Guttenberg on 30.04.2018.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTInstantTargetRestorationConfiguration_h
#define WTInstantTargetRestorationConfiguration_h

#import <Foundation/NSObject.h>


NS_ASSUME_NONNULL_BEGIN

/**
 * Describes the expansion behaviour that should be used by the Wikitude SDK
 */
typedef NS_ENUM(NSInteger, WTInstantTargetExpansionPolicy) {
  /**
   * A loaded instant target can and will be expanded. This means that an instant tracker can continue tracking even though the current scene now contains more information compared to its creation time.
   */
    WTInstantTargetExpansionPolicyAllowExpansion,
  /**
   * A loaded instant target will not be expanded even though its instant tracker might discover new areas of the scene.
   */
    WTInstantTargetExpansionPolicyDisallowExpansion
};

/**
 * @brief This class is used to provide further details on how an existing instant target should be restored.
 */
@interface WTInstantTargetRestorationConfiguration : NSObject

/**
 * The expansion policy describes if the SDK should add new feature points to the instant target or not. Adding more feature points improves tracking robustness while requiring more CPU power.
 */
@property (nonatomic, assign) WTInstantTargetExpansionPolicy instantTargetExpansionPolicy;

@end

NS_ASSUME_NONNULL_END

#endif /* WTInstantTargetRestorationConfiguration_h */

