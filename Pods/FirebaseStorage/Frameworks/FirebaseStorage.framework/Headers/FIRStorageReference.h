// clang-format off
/** @file FIRStorageReference.h
    @brief Firebase SDK
    @copyright Copyright 2016 Google Inc.
    @remarks Use of this SDK is subject to the Google APIs Terms of Service:
    https://developers.google.com/terms/
    */
// clang-format on

#import <Foundation/Foundation.h>

#import "FIRStorage.h"
#import "FIRStorageConstants.h"
#import "FIRStorageDownloadTask.h"
#import "FIRStorageMetadata.h"
#import "FIRStorageTask.h"
#import "FIRStorageUploadTask.h"

NS_ASSUME_NONNULL_BEGIN

/**
 * FIRStorageReference represents a reference to a Google Cloud Storage object. Developers can
 * upload and download objects, as well as get/set object metadata, and delete an object at the
 * path.
 * @see https://cloud.google.com/storage/
 */
@interface FIRStorageReference : NSObject

/**
 * The FIRStorage service object which created this reference.
 */
@property(nonatomic, readonly) FIRStorage *storage;

/**
 * The name of the Google Cloud Storage bucket associated with this reference,
 * in gs://bucket/path/to/object.txt, the bucket would be: 'bucket'
 */
@property(nonatomic, readonly) NSString *bucket;

/**
 * The full path to this object, not including the Google Cloud Storage bucket.
 * In gs://bucket/path/to/object.txt, the full path would be: 'path/to/object.txt'
 */
@property(nonatomic, readonly) NSString *fullPath;

/**
 * The short name of the object associated with this reference,
 * in gs://bucket/path/to/object.txt, the name of the object would be: 'object.txt'
 */
@property(nonatomic, readonly) NSString *name;

#pragma mark - Path Operations

/**
 * Creates a new FIRStorageReference pointing to the root object.
 * @return A new FIRStorageReference pointing to the root object.
 */
- (FIRStorageReference *)root;

/**
 * Creates a new FIRStorageReference pointing to the parent of the current reference
 * or nil if this instance references the root location.
 * For example:
 *   path = foo/bar/baz   parent = foo/bar
 *   path = foo           parent = (root)
 *   path = (root)        parent = nil
 * @return A new FIRStorageReference pointing to the parent of the current reference.
 */
- (nullable FIRStorageReference *)parent;

/**
 * Creates a new FIRStorageReference pointing to a child object of the current reference.
 *   path = foo      child = bar    newPath = foo/bar
 *   path = foo/bar  child = baz    newPath = foo/bar/baz
 * All leading and trailing slashes will be removed, and consecutive slashes will be
 * compressed to single slashes. For example:
 *   child = /foo/bar     newPath = foo/bar
 *   child = foo/bar/     newPath = foo/bar
 *   child = foo///bar    newPath = foo/bar
 * @param path Path to append to the current path.
 * @return A new FIRStorageReference pointing to a child location of the current reference.
 */
- (FIRStorageReference *)child:(NSString *)path;

#pragma mark - Uploads

/**
 * Asynchronously uploads data to the currently specified FIRStorageReference,
 * without additional metadata.
 * This is not recommended for large files, and one should instead upload a file from disk.
 * @param uploadData The NSData to upload.
 * @return An instance of FIRStorageUploadTask, which can be used to monitor or manage the upload.
 */
- (FIRStorageUploadTask *)putData:(NSData *)uploadData;

/**
 * Asynchronously uploads data to the currently specified FIRStorageReference.
 * This is not recommended for large files, and one should instead upload a file from disk.
 * @param uploadData The NSData to upload.
 * @param metadata FIRStorageMetadata containing additional information (MIME type, etc.)
 * about the object being uploaded.
 * @return An instance of FIRStorageUploadTask, which can be used to monitor or manage the upload.
 */
- (FIRStorageUploadTask *)putData:(NSData *)uploadData
                         metadata:(nullable FIRStorageMetadata *)metadata;

/**
 * Asynchronously uploads data to the currently specified FIRStorageReference.
 * This is not recommended for large files, and one should instead upload a file from disk.
 * @param uploadData The NSData to upload.
 * @param metadata FIRStorageMetadata containing additional information (MIME type, etc.)
 * about the object being uploaded.
 * @param completion A completion block that either returns the object metadata on success,
 * or an error on failure.
 * @return An instance of FIRStorageUploadTask, which can be used to monitor or manage the upload.
 */
- (FIRStorageUploadTask *)putData:(NSData *)uploadData
                         metadata:(nullable FIRStorageMetadata *)metadata
                       completion:(nullable void (^)(FIRStorageMetadata *_Nullable metadata,
                                                     NSError *_Nullable error))completion;

/**
 * Asynchronously uploads a file to the currently specified FIRStorageReference,
 * without additional metadata.
 * @param fileURL A URL representing the system file path of the object to be uploaded.
 * @return An instance of FIRStorageUploadTask, which can be used to monitor or manage the upload.
 */
- (FIRStorageUploadTask *)putFile:(NSURL *)fileURL;

/**
 * Asynchronously uploads a file to the currently specified FIRStorageReference.
 * @param fileURL A URL representing the system file path of the object to be uploaded.
 * @param metadata FIRStorageMetadata containing additional information (MIME type, etc.)
 * about the object being uploaded.
 * @return An instance of FIRStorageUploadTask, which can be used to monitor or manage the upload.
 */
- (FIRStorageUploadTask *)putFile:(NSURL *)fileURL metadata:(nullable FIRStorageMetadata *)metadata;

/**
 * Asynchronously uploads a file to the currently specified FIRStorageReference.
 * @param fileURL A URL representing the system file path of the object to be uploaded.
 * @param metadata FIRStorageMetadata containing additional information (MIME type, etc.)
 * about the object being uploaded.
 * @param completion A completion block that either returns the object metadata on success,
 * or an error on failure.
 * @return An instance of FIRStorageUploadTask, which can be used to monitor or manage the upload.
 */
- (FIRStorageUploadTask *)putFile:(NSURL *)fileURL
                         metadata:(nullable FIRStorageMetadata *)metadata
                       completion:(nullable void (^)(FIRStorageMetadata *_Nullable metadata,
                                                     NSError *_Nullable error))completion;

#pragma mark - Downloads

/**
 * Asynchronously downloads the object at the FIRStorageReference to an NSData object in memory.
 * An NSData of the provided max size will be allocated, so ensure that the device has enough free
 * memory to complete the download. For downloading large files, writeToFile may be a better option.
 * @param size The maximum size in bytes to download. If the download exceeds this size
 * the task will be cancelled and an error will be returned.
 * @param completion A completion block that either returns the object data on success,
 * or an error on failure.
 * @return An FIRStorageDownloadTask that can be used to monitor or manage the download.
 */
- (FIRStorageDownloadTask *)dataWithMaxSize:(int64_t)size
                                 completion:(void (^)(NSData *_Nullable data,
                                                      NSError *_Nullable error))completion;

/**
 * Asynchronously retrieves a long lived download URL with a revokable token.
 * This can be used to share the file with others, but can be revoked by a developer
 * in the Firebase Console if desired.
 * @param completion A completion block that either returns the URL on success,
 * or an error on failure.
 */
- (void)downloadURLWithCompletion:(void (^)(NSURL *_Nullable URL,
                                            NSError *_Nullable error))completion;

/**
 * Asynchronously downloads the object at the current path to a specified system filepath.
 * @param fileURL A file system URL representing the path the object should be downloaded to.
 * @return An FIRStorageDownloadTask that can be used to monitor or manage the download.
 */
- (FIRStorageDownloadTask *)writeToFile:(NSURL *)fileURL;

/**
 * Asynchronously downloads the object at the current path to a specified system filepath.
 * @param fileURL A file system URL representing the path the object should be downloaded to.
 * @param completion A completion block that fires when the file download completes.
 * Returns an NSURL pointing to the file path of the downloaded file on success,
 * or an error on failure.
 * @return An FIRStorageDownloadTask that can be used to monitor or manage the download.
 */
- (FIRStorageDownloadTask *)writeToFile:(NSURL *)fileURL
                             completion:(nullable void (^)(NSURL *_Nullable URL,
                                                           NSError *_Nullable error))completion;

#pragma mark - Metadata Operations

/**
 * Retrieves metadata associated with an object at the current path.
 * @param completion A completion block which returns the object metadata on success,
 * or an error on failure.
 */
- (void)metadataWithCompletion:(void (^)(FIRStorageMetadata *_Nullable metadata,
                                         NSError *_Nullable error))completion;

/**
 * Updates the metadata associated with an object at the current path.
 * @param metadata An FIRStorageMetadata object with the metadata to update.
 * @param completion A completion block which returns the FIRStorageMetadata on success,
 * or an error on failure.
 */
- (void)updateMetadata:(FIRStorageMetadata *)metadata
            completion:(nullable void (^)(FIRStorageMetadata *_Nullable metadata,
                                          NSError *_Nullable error))completion;

#pragma mark - Delete

/**
 * Deletes the object at the current path.
 * @param completion A completion block which returns nil on success, or an error on failure.
 */
- (void)deleteWithCompletion:(nullable void (^)(NSError *_Nullable error))completion;

@end

NS_ASSUME_NONNULL_END
