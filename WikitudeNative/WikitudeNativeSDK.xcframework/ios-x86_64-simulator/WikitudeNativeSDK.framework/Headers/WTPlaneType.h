//
//  WTPlaneType.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 27.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTPlaneType_h
#define WTPlaneType_h

/** @typedef WTPlaneType Defines a plane's orientation. */
typedef NS_ENUM(NSUInteger, WTPlaneType) {
    /** HorizontalUpward: The detected plane is horizontal and points upward (e.g. floor). */
    WTPlaneType_HorizontalUpward,
    /** HorizontalDownward: The detected plane is horizontal and points downward (e.g. ceiling). */
    WTPlaneType_HorizontalDownward,
    /** Vertical: The detected plane is vertical (e.g. wall). */
    WTPlaneType_Vertical,
    /** Arbitrary: The detected plane has an arbitrary orientation. */
    WTPlaneType_Arbitrary
};

#endif /* WTPlaneType_h */
