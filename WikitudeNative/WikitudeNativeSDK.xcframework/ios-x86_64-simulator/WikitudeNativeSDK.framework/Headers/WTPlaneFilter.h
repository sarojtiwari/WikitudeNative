//
//  WTPlaneFilter.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 27.08.18.
//  Copyright © 2018 Wikitude. All rights reserved.
//

#ifndef WTPlaneFilter_h
#define WTPlaneFilter_h

/** @typedef WTPlaneFilter Permits to filter planes by orientation. */
typedef NS_OPTIONS(NSUInteger, WTPlaneFilter) {
    /** HorizontalUpward: The plane to detect is horizontal and points upward (e.g. floor). */
    WTPlaneFilter_HorizontalUpward = 1 << 0,
    /** HorizontalDownward: The plane to detect is horizontal and points downward (e.g. ceiling). */
    WTPlaneFilter_HorizontalDownward = 1 << 1,
    /** Horizontal: The plane to detect is horizontal (e.g. floor). */
    WTPlaneFilter_Horizontal = 1 << 2,
    /** Vertical: The plane to detect plane is vertical (e.g. wall). */
    WTPlaneFilter_Vertical = 1 << 3,
    /** Arbitrary: The plane to detect has an arbitrary orientation. */
    WTPlaneFilter_Arbitrary = 1 << 4,
    /** Arbitrary: The plane to detect has any of the above orientations. */
    WTPlaneFilter_Any = 1 << 5
};

#endif /* WTPlaneFilter_h */
