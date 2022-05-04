//
//  WTExtendedTrackingQuality.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 20.04.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#import <Foundation/NSObjCRuntime.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * WTExtendedTrackingQuality indicates the current extended tracking quality and how likely it is, that extended tracking will work.
 */
typedef NS_ENUM(NSInteger, WTExtendedTrackingQuality) {
    /**
     * WTExtendedTrackingQuality_Bad indicates that no extended tracking would work, if the target moves out of the camera image.
     */
    WTExtendedTrackingQuality_Bad = -1,

    /**
     * WTExtendedTrackingQuality_Average indicates that extended tracking might work, but not very likely or very good.
     */
    WTExtendedTrackingQuality_Average,

    /**
     * WTExtendedTrackingQuality_Good indicates that extended tracking will work very likely and stable.
     */
    WTExtendedTrackingQuality_Good
};

NS_ASSUME_NONNULL_END
