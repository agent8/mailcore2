//
//  MCOAbstractPart.h
//  mailcore2
//
//  Created by DINH Viêt Hoà on 3/10/13.
//  Copyright (c) 2013 MailCore. All rights reserved.
//

#ifndef MAILCORE_MCOABSTRACTPART_H

#define MAILCORE_MCOABSTRACTPART_H

#import <Foundation/Foundation.h>
#include <MailCore/MCOConstants.h>

@class MCOAbstractMessage;

typedef NS_ENUM(NSInteger, MCOPartType) {
    // Used for a single part.
    // The part will be a MCOAbstractPart.
    MCOPartTypeSingle,
    
    // Used for a message part (MIME type: message/rfc822).
    // The part will be a MCOAbstractMessagePart.
    // It's when a message is sent as attachment of an other message.
    MCOPartTypeMessage,
    
    // Used for a multipart, multipart/mixed.
    // The part will be a MCOAbstractMultipart.
    MCOPartTypeMultipartMixed,
    
    // Used for a multipart, multipart/related.
    // The part will be a MCOAbstractMultipart.
    MCOPartTypeMultipartRelated,
    
    // Used for a multipart, multipart/alternative.
    // The part will be a MCOAbstractMultipart.
    MCOPartTypeMultipartAlternative,
    
    // Used for a signed message, multipart/signed.
    // The part will be a MCOAbstractMultipart.
    MCOPartTypeMultipartSigned,
};

#ifdef __cplusplus
namespace mailcore {
    class AbstractPart;
}
#endif

@interface MCOAbstractPart : NSObject <NSCopying>

- (instancetype) init;
#ifdef __cplusplus
- (instancetype) initWithMCPart:(mailcore::AbstractPart *)part NS_DESIGNATED_INITIALIZER;
#endif

/** A part identifier looks like 1.2.1 */
@property (nonatomic, copy) NSString * _Nullable partID;

/** Returns type of the part (single / message part / multipart/mixed,
 multipart/related, multipart/alternative). See MCOPartType.*/
@property (nonatomic, assign) MCOPartType partType;

/** Returns filename of the part.*/
@property (nonatomic, copy) NSString * _Nullable filename;

/** Returns MIME type of the part. For example application/data.*/
@property (nonatomic, copy) NSString * _Nullable mimeType;

/** Returns charset of the part in case it's a text single part.*/
@property (nonatomic, copy) NSString * _Nullable charset;

/** Returns the unique ID generated for this part.
 It's a unique identifier that's created when the object is created manually
 or created by the parser.*/
@property (nonatomic, copy) NSString * _Nullable uniqueID;

/** Returns the value of the Content-ID field of the part.*/
@property (nonatomic, copy) NSString * _Nullable contentID;

/** Returns the value of the Content-Location field of the part.*/
@property (nonatomic, copy) NSString * _Nullable contentLocation;

/** Returns the value of the Content-Description field of the part.*/
@property (nonatomic, copy) NSString * _Nullable contentDescription;

/** Returns whether the part is an explicit inline attachment.*/
@property (nonatomic, assign, getter=isInlineAttachment) BOOL inlineAttachment;

/** Returns whether the part is an explicit attachment.*/
@property (nonatomic, assign, getter=isAttachment) BOOL attachment;

/** It's the encoding of the single part */
@property (nonatomic, nonatomic) MCOEncoding encoding;

/** The size of the single part in bytes */
@property (nonatomic, nonatomic) unsigned int size;

/** Returns the part with the given Content-ID among this part and its subparts.*/
- (MCOAbstractPart *) partForContentID:(NSString *)contentID;

/** Returns the part with the given unique identifier among this part and its subparts.*/
- (MCOAbstractPart *) partForUniqueID:(NSString *)uniqueID;

/** Returns a string representation of the data according to charset.*/
- (NSString *) decodedStringForData:(NSData *)data;

/** Adds a content type parameter.*/
- (void) setContentTypeParameterValue:(NSString *)value forName:(NSString *)name;

/** Remove a given content type parameter.*/
- (void) removeContentTypeParameterForName:(NSString *)name;

/** Returns the value of a given content type parameter.*/
- (NSString *) contentTypeParameterValueForName:(NSString *)name;

/** Returns an array with the names of all content type parameters.*/
- (NSArray * /* NSString */) allContentTypeParametersNames;


/**
 Returns the decoded size of the part.
 For example, for a part that's encoded with base64, it will return actual_size * 3/4.
 */
- (unsigned int) decodedSize;
@end

@interface MCOAbstractPart (MCOUnavailable)


#pragma mark - Unavailable initializers

/** Do not invoke this directly. */
- (instancetype) init NS_UNAVAILABLE;
/** Do not invoke this directly. */
+ (instancetype) new NS_UNAVAILABLE;

@end

#endif
