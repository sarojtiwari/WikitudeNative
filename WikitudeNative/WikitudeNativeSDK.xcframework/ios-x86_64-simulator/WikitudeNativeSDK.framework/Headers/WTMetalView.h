//
//  WTMetalView.h
//  WikitudeSDK
//
//  Created by Andreas Schacherbauer on 30.09.17.
//  Copyright © 2017 Wikitude. All rights reserved.
//

#import <TargetConditionals.h>

#if TARGET_OS_IOS
#import <UIKit/UIView.h>
#else
#import <AppKit/NSView.h>
#endif


@class WTRenderer;
#if TARGET_OS_IOS
@interface WTMetalView : UIView
#else
@interface WTMetalView : NSView
#endif
@property (nonatomic, weak) WTRenderer      *renderer;
@end
