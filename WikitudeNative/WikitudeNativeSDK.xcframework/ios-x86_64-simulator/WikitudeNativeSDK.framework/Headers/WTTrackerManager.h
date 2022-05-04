//
//  WTTrackerManager.h
//  WikitudeNativeSDK
//
//  Created by Andreas Schacherbauer on 28/04/15.
//  Copyright (c) 2015 Wikitude. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "WTDeprecation.h"
#import "WTTargetCollectionResource.h"
#import "WTCloudRecognitionService.h"


NS_ASSUME_NONNULL_BEGIN

/**
 * WTCloudRecognitionServerRegion defines the possible cloud recognition server regions that are available.
 * The region should be set depending on where the final application will be used most likely.
 * If the region does not match the actual user location, longer round trip times should be expected.
 */
typedef NS_ENUM(NSInteger, WTCloudRecognitionServerRegion) {
    /**
     * WTCloudRecognitionServerRegion_Americas should be used when the user is currently in North or South America.
     */
    WTCloudRecognitionServerRegion_Americas,

    /**
     * WTCloudRecognitionServerRegion_Europe should be used when the user is currently in Europe, Africa or Middle East.
     */
    WTCloudRecognitionServerRegion_Europe
};

@protocol WTTargetCollectionResourceDelegate;
@class WTImageTrackerConfiguration;
@class WTImageTracker;
@protocol WTImageTrackerDelegate;
@class WTBaseTracker;
@class WTClientTracker;
@protocol WTClientTrackerDelegate;
@class WTCloudTracker;
@protocol WTCloudTrackerDelegate;
@class WTInstantTrackerConfiguration;
@class WTInstantTracker;
@protocol WTInstantTrackerDelegate;
@class WTCloudRecognitionService;
@class WTCloudRecognitionServiceConfiguration;
@class WTObjectTrackerConfiguration;
@class WTObjectTracker;
@protocol WTObjectTrackerDelegate;

/**
 * WTTrackerManger provides factory methods to create certain tracker objects.
 */
@interface WTTrackerManager : NSObject

/**
 * @brief Returns a weak pointer to a newly created WTTargetCollectionResource object, used to load a target collection file.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param resourceURL A URL from where the target collection resource should be loaded from. Files can be loaded from the application bundle or a remote server.
 * @return WTTargetCollectionResource * A pointer to a newly created WTTargetCollectionResource object.
 */
- (WTTargetCollectionResource *)createTargetCollectionResourceFromURL:(NSURL *)resourceURL;

/**
 * @deprecated Use createTargetCollectionResourceFromURL: instead
 *
 * @brief Returns a weak pointer to a newly created WTTargetCollectionResource object, used to load a target collection file.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param resourceURL A URL from where the target collection resource should be loaded from. Files can be loaded from the application bundle or a remote server.
 * @param errorHandler An object that conforms to the WTTargetCollectionResourceCompletionHandler protocol.
 * @return WTTargetCollectionResource * A pointer to a newly created WTTargetCollectionResource object.
 */
- (WTTargetCollectionResource *)createTargetCollectionResourceFromURL:(NSURL *)resourceURL completion:(WTTargetCollectionResourceCompletionHandler)errorHandler WT_DEPRECATED_SINCE(8.0.0, "Use createTargetCollectionResourceFromURL: instead.");

/**
 * @brief Returns a weak pointer to a newly created WTCloudRecognitionService object, used to offload image target recognition to the Wikitude cloud recognition servers.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param clientToken The client token that is associated with your Wikitude cloud recognition account.
 * @param groupId The groupId that is associated with your Wikitude cloud recognition account.
 * @param targetCollectionId The identifier for the target collection that should be loaded on the Wikitude cloud recognition server.
 * @param completionHandler An object that conforms to the WTCloudRecognitionServiceInitializationHandler protocol.
 * @return WTCloudRecognitionService * A pointer to a newly created WTCloudRecognitionService object.
 */
- (WTCloudRecognitionService *)createCloudRecognitionServiceWithClientToken:(NSString *)clientToken groupId:(NSString *)groupId targetCollectionId:(NSString *)targetCollectionId completion:(WTCloudRecognitionServiceInitializationHandler)completionHandler;

/**
 * @brief Returns a weak pointer to a newly created WTCloudRecognitionService object, used to offload image target recognition to the Wikitude cloud recognition servers.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param clientToken The client token that is associated with your Wikitude cloud recognition account.
 * @param targetCollectionId The identifier for the target collection that should be loaded on the Wikitude cloud recognition server.
 * @param completionHandler An object that conforms to the WTCloudRecognitionServiceInitializationHandler protocol.
 * @return WTCloudRecognitionService * A pointer to a newly created WTCloudRecognitionService object.
 */
- (WTCloudRecognitionService *)createCloudRecognitionServiceWithClientToken:(NSString *)clientToken targetCollectionId:(NSString *)targetCollectionId completion:(WTCloudRecognitionServiceInitializationHandler)completionHandler WT_DEPRECATED_SINCE(8.1.0, "Use createCloudRecognitionServiceWithClientToken:groupId:targetCollectionId:completion: instead.");

/**
 * @brief Returns a weak pointer to a newly created WTCloudRecognitionService object, used to offload image target recognition to the Wikitude cloud recognition servers.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param clientToken The client token that is associated with your Wikitude cloud recognition account.
 * @param groupId The groupId that is associated with your Wikitude cloud recognition account.
 * @param targetCollectionId The identifier for the target collection that should be loaded on the Wikitude cloud recognition server.
 * @param configuration The configuration that should be used when the WTCloudRecognitionService is created. Please have a look at WTCloudRecognitionServiceConfiguration for all possible configurations.
 * @param completionHandler An object that conforms to the WTCloudRecognitionServiceInitializationHandler protocol.
 * @return WTCloudRecognitionService * A pointer to a newly created WTCloudRecognitionService object.
 */
- (WTCloudRecognitionService *)createCloudRecognitionServiceWithClientToken:(NSString *)clientToken groupId:(NSString *)groupId targetCollectionId:(NSString *)targetCollectionId configuration:(nullable void (^)(WTCloudRecognitionServiceConfiguration *cloudRecognitionServiceConfiguration))configuration completion:(WTCloudRecognitionServiceInitializationHandler)completionHandler;

/**
 * @brief Returns a weak pointer to a newly created WTCloudRecognitionService object, used to offload image target recognition to the Wikitude cloud recognition servers.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param clientToken The client token that is associated with your Wikitude cloud recognition account.
 * @param targetCollectionId The identifier for the target collection that should be loaded on the Wikitude cloud recognition server.
 * @param configuration The configuration that should be used when the WTCloudRecognitionService is created. Please have a look at WTCloudRecognitionServiceConfiguration for all possible configurations.
 * @param completionHandler An object that conforms to the WTCloudRecognitionServiceInitializationHandler protocol.
 * @return WTCloudRecognitionService * A pointer to a newly created WTCloudRecognitionService object.
 */
- (WTCloudRecognitionService *)createCloudRecognitionServiceWithClientToken:(NSString *)clientToken targetCollectionId:(NSString *)targetCollectionId configuration:(nullable void (^)(WTCloudRecognitionServiceConfiguration *cloudRecognitionServiceConfiguration))configuration completion:(WTCloudRecognitionServiceInitializationHandler)completionHandler WT_DEPRECATED_SINCE(8.1.0, "Use createCloudRecognitionServiceWithClientToken:groupId:targetCollectionId:configuration:completion: instead.");

/**
 * @brief Returns a weak pointer to a newly created WTImageTracker object, configured for 2d tracking using a wtc file loaded by a WTTargetCollectionResource.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property. In case the given target collection resource is not yet loading, `-load:` would be called.
 *
 * @param targetCollectionResource The target collection resource used to load the wtc file.
 * @param delegate An object that conforms to the WTImageTrackerDelegate protocol.
 * @param configuration A configuration object used to define how the image tracker behaves.
 * @return WTImageTracker * A pointer to a newly created WTImageTracker object.
 */
- (WTImageTracker *)createImageTrackerFromTargetCollectionResource:(WTTargetCollectionResource *)targetCollectionResource delegate:(id<WTImageTrackerDelegate>)delegate configuration:(nullable void (^)(WTImageTrackerConfiguration * imageTrackerConfiguration))configuration;

/**
 * @brief Returns a weak pointer to a newly created WTImageTracker object, configured for 2d tracking using the WTCloudRecognitionService to offload recognition to the Wikitude cloud recognition servers.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param cloudRecognitionService The cloud recognition service used to communicate with the Wikitude cloud recognition servers.
 * @param delegate An object that conforms to the WTImageTrackerDelegate protocol.
 * @param configuration A configuration object used to define how the image tracker behaves.
 * @return WTImageTracker * A pointer to a newly created WTImageTracker object.
 */
- (WTImageTracker *)createImageTrackerFromCloudRecognitionService:(WTCloudRecognitionService *)cloudRecognitionService delegate:(id<WTImageTrackerDelegate>)delegate configuration:(nullable void (^)(WTImageTrackerConfiguration * imageTrackerConfiguration))configuration;

/**
 * @brief Returns a weak pointer to a newly created WTObjectTracker object, configured for 3d tracking using a wmc file loaded by a WTTargetCollectionResource.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property. In case the given target collection resource is not yet loading, `-load:` would be called.
 *
 * @param targetCollectionResource The target collection resource used to load the wmc file.
 * @param delegate An object that conforms to the WTObjectTrackerDelegate protocol.
 * @return WTObjectTracker * A pointer to a newly created WTObjectTracker object.
 */
- (WTObjectTracker *)createObjectTrackerFromTargetCollectionResource:(WTTargetCollectionResource *)targetCollectionResource delegate:(id<WTObjectTrackerDelegate>)delegate WT_DEPRECATED_SINCE(8.0.0, "Use -createObjectTrackerFromTargetCollectionResource:delegate:configuration: instead");

/**
 * @brief Returns a weak pointer to a newly created WTObjectTracker object, configured for 3d tracking using a wmc file loaded by a WTTargetCollectionResource.
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property. In case the given target collection resource is not yet loading, `-load:` would be called.
 *
 * @param targetCollectionResource The target collection resource used to load the wmc file.
 * @param delegate An object that conforms to the WTObjectTrackerDelegate protocol.
 * @param configuration A configuration object used to define how the image tracker behaves.
 * @return WTObjectTracker * A pointer to a newly created WTObjectTracker object.
 */
- (WTObjectTracker *)createObjectTrackerFromTargetCollectionResource:(WTTargetCollectionResource *)targetCollectionResource delegate:(id<WTObjectTrackerDelegate>)delegate configuration:(nullable void (^)(WTObjectTrackerConfiguration *objectTrackerConfiguration))configuration;

/**
 * @brief Returns a weak pointer to a newly created WTInstantTracker object, configured for 3d tracking of a scene without any markers
 *
 * @discussion Callers need to make sure to retain the reference count e.g. by assigning to a strong property.
 *
 * @param delegate An object that conforms to the WTObjectTrackerDelegate protocol.
 * @param configuration A configuration object used to define how the instant tracker should behave.
 * @return WTObjectTracker * A pointer to a newly created WTObjectTracker object.
 */
- (WTInstantTracker *)createInstantTracker:(id<WTInstantTrackerDelegate>)delegate configuration:(nullable void (^)(WTInstantTrackerConfiguration *instantTrackerConfiguration))configuration;

/**
 * @brief Returns a boolean value indicating whether SMART will be able to run using ARKit.
 *
 * @return bool The returned value is true if ARKit is available, false otherwise.
 */
- (bool)isPlatformAssistedTrackingSupported;

/** @brief Enables a custom Tracker configuration to be applied.
 *
 *  @param configuration A JSON String containing the custom configuration for Trackers.
 *  @return bool The returned value is true if the custom tracker configuration is set successfuly, false otherwise.
 */
- (bool)setCustomTrackerConfiguration:(NSString*)configuration;

@end

NS_ASSUME_NONNULL_END
