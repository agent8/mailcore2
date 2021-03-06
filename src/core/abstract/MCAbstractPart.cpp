#include "MCWin32.h" // should be first include.

#include "MCAbstractPart.h"

#include <string.h>
#include <stdlib.h>
#include <libetpan/libetpan.h>
#include "MCData.h"
#include "MCAbstractMessagePart.h"
#include "MCAbstractMultipart.h"
#include "MCArray.h"

using namespace mailcore;

AbstractPart::AbstractPart()
{
    init();
}

AbstractPart::AbstractPart(AbstractPart * other)
{
    init();
    setPartID(other->mPartID);
    setUniqueID(other->mUniqueID);
    setFilename(other->mFilename);
    setMimeType(other->mMimeType);
    setCharset(other->mCharset);
    setContentID(other->mContentID);
    setContentLocation(other->mContentLocation);
    setContentDescription(other->mContentDescription);
    setInlineAttachment(other->mInlineAttachment);
    setAttachment(other->mAttachment);
    setPartType(other->mPartType);
    setContentTypeParameters(other->mContentTypeParameters);
    setEncoding(other->mEncoding);
    setSize(other->mSize);
}

void AbstractPart::init()
{
    mPartID = NULL;
    mUniqueID = NULL;
    mFilename = NULL;
    mMimeType = NULL;
    mCharset = NULL;
    mContentID = NULL;
    mContentLocation = NULL;
    mContentDescription = NULL;
    mInlineAttachment = false;
    mAttachment = false;
    mPartType = PartTypeSingle;
    mContentTypeParameters = NULL;
    mEncoding = Encoding8Bit;
    mSize = 0;
}

AbstractPart::~AbstractPart()
{
    MC_SAFE_RELEASE(mPartID);
    MC_SAFE_RELEASE(mUniqueID);
    MC_SAFE_RELEASE(mFilename);
    MC_SAFE_RELEASE(mMimeType);
    MC_SAFE_RELEASE(mCharset);
    MC_SAFE_RELEASE(mContentID);
    MC_SAFE_RELEASE(mContentLocation);
    MC_SAFE_RELEASE(mContentDescription);
    MC_SAFE_RELEASE(mContentTypeParameters);
}

String * AbstractPart::description()
{
    String * result = String::string();
    result->appendUTF8Format("<%s:%p\n", className()->UTF8Characters(), this);
    if (mPartID != NULL) {
        result->appendUTF8Format("partID: %s\n", mPartID->UTF8Characters());
    }
    if (mFilename != NULL) {
        result->appendUTF8Format("filename: %s\n", mFilename->UTF8Characters());
    }
    if (mMimeType != NULL) {
        result->appendUTF8Format("mime type: %s\n", mMimeType->UTF8Characters());
    }
    if (mCharset != NULL) {
        result->appendUTF8Format("charset: %s\n", mCharset->UTF8Characters());
    }
    if (mContentID != NULL) {
        result->appendUTF8Format("content-ID: %s\n", mContentID->UTF8Characters());
    }
    if (mContentLocation != NULL) {
        result->appendUTF8Format("content-location: %s\n", mContentLocation->UTF8Characters());
    }
    if (mContentDescription != NULL) {
        result->appendUTF8Format("content-description: %s\n", mContentDescription->UTF8Characters());
    }
    result->appendUTF8Format("inline: %i\n", mInlineAttachment);
    result->appendUTF8Format("attachment: %i\n", mAttachment);
    result->appendUTF8Format("encoding:%d\n",mEncoding);
    result->appendUTF8Format("size:%d\n",mSize);
    if (mContentTypeParameters != NULL) {
        mc_foreachhashmapKeyAndValue(String, key, String, value, mContentTypeParameters) {
            result->appendUTF8Format("%s: %s\n", key->UTF8Characters(), value->UTF8Characters());
        }
    }
    result->appendUTF8Format(">");
    
    return result;
}

Object * AbstractPart::copy()
{
    return new AbstractPart(this);
}

void AbstractPart::setPartID(String * partID)
{
    MC_SAFE_REPLACE_COPY(String, mPartID, partID);
}

String * AbstractPart::partID()
{
    return mPartID;
}

PartType AbstractPart::partType()
{
    return mPartType;
}

void AbstractPart::setPartType(PartType type)
{
    mPartType = type;
}

String * AbstractPart::uniqueID()
{
    return mUniqueID;
}

void AbstractPart::setUniqueID(String * uniqueID)
{
    MC_SAFE_REPLACE_COPY(String, mUniqueID, uniqueID);
}

String * AbstractPart::filename()
{
    return mFilename;
}

void AbstractPart::setFilename(String * filename)
{
    MC_SAFE_REPLACE_COPY(String, mFilename, filename);
}

String * AbstractPart::mimeType()
{
    return mMimeType;
}

void AbstractPart::setMimeType(String * mimeType)
{
    MC_SAFE_REPLACE_COPY(String, mMimeType, mimeType);
}

String * AbstractPart::charset()
{
    return mCharset;
}

void AbstractPart::setCharset(String * charset)
{
    MC_SAFE_REPLACE_COPY(String, mCharset, charset);
}

String * AbstractPart::contentID()
{
    return mContentID;
}

void AbstractPart::setContentID(String * contentID)
{
    MC_SAFE_REPLACE_COPY(String, mContentID, contentID);
}

String * AbstractPart::contentLocation()
{
    return mContentLocation;
}

void AbstractPart::setContentLocation(String * contentLocation)
{
    MC_SAFE_REPLACE_COPY(String, mContentLocation, contentLocation);
}

String * AbstractPart::contentDescription()
{
    return mContentDescription;
}

void AbstractPart::setContentDescription(String * contentDescription)
{
    MC_SAFE_REPLACE_COPY(String, mContentDescription, contentDescription);
}

bool AbstractPart::isInlineAttachment()
{
    return mInlineAttachment;
}

void AbstractPart::setInlineAttachment(bool inlineAttachment)
{
    mInlineAttachment = inlineAttachment;
}

bool AbstractPart::isAttachment()
{
    return mAttachment;
}

void AbstractPart::setAttachment(bool attachment)
{
    mAttachment = attachment;
}

void AbstractPart::importIMAPFields(struct mailimap_body_fields * fields,
    struct mailimap_body_ext_1part * extension)
{
    if (fields->bd_id != NULL) {
        char * contentid;
        size_t cur_token;
        int r;
        
        cur_token = 0;
        r = mailimf_msg_id_parse(fields->bd_id, strlen(fields->bd_id),
            &cur_token, &contentid);
        if (r == MAILIMF_NO_ERROR) {
            // msg id
            setContentID(String::stringWithUTF8Characters(contentid));
            free(contentid);
        }
    }
    if (fields->bd_description != NULL) {
        setContentDescription(String::stringWithUTF8Characters(fields->bd_description));
    }
    if (fields->bd_encoding != NULL) {
        bool isUUEncode;
        
        isUUEncode = false;
        if (fields->bd_encoding->enc_type == MAILIMAP_BODY_FLD_ENC_OTHER) {
            if (strcasecmp(fields->bd_encoding->enc_value, "x-uuencode") == 0 ||
                strcasecmp(fields->bd_encoding->enc_value, "uuencode") == 0) {
                isUUEncode = true;
            }
        }
        if (isUUEncode) {
            setEncoding(EncodingUUEncode);
        }
        else {
            setEncoding((Encoding) fields->bd_encoding->enc_type);
        }
    }
    setSize(fields->bd_size);
    if (extension != NULL) {
        if (extension->bd_disposition != NULL) {
            if (strcasecmp(extension->bd_disposition->dsp_type, "inline") == 0) {
                setInlineAttachment(true);
            }
            else if (strcasecmp(extension->bd_disposition->dsp_type, "attachment") == 0) {
                setAttachment(true);
            }

            if (extension->bd_disposition->dsp_attributes != NULL) {
                    clistiter * cur;
                    String *filename = NULL;
                    for(cur = clist_begin(extension->bd_disposition->dsp_attributes->pa_list) ; cur != NULL ;
                        cur = clist_next(cur)) {
                        struct mailimap_single_body_fld_param * imap_param;
                        //Know issue for outlook:outlook IMAP does not support filename*
                        //eg.  filename*0*=utf-8''%E7%94%9F%E5%AD%97%E6%B5%8B%E8%AF; filename*1*=%95.rtf
                        //("attachment" ("filename" "utf-8''%E7%94%9F%E5%AD%97%E6%B5%8B%E8%AF")) NIL NIL)
                        imap_param = (struct mailimap_single_body_fld_param *) clist_content(cur);
                        if (strcasecmp(imap_param->pa_name, "filename") == 0) {
                            filename = String::stringByDecodingMIMEHeaderValue(imap_param->pa_value);
                            break;
                        } else if (strncasecmp(imap_param->pa_name, "filename*", 9) == 0) {
                            String * filenamePart = String::stringByDecodingMIMEHeaderValueRfc2231(imap_param->pa_value);
                            if (filenamePart == NULL) {
                                filenamePart = String::stringByDecodingMIMEHeaderValue(imap_param->pa_value);
                            }
                            if (filename == NULL) {
                                filename = filenamePart;
                            } else {
                                filename->appendString(filenamePart);
                            }
                        } else {
                            MCLog("Extension:%s->%s\n",imap_param->pa_name,imap_param->pa_value);
                        }
                    }
                    if (filename != NULL) {
                        setFilename(filename);
                    }
            }
        }
        
        if (extension->bd_loc != NULL) {
            setContentLocation(String::stringWithUTF8Characters(extension->bd_loc));
        }
    }
    
    if (fields->bd_parameter != NULL) {
        clistiter * cur;
        for(cur = clist_begin(fields->bd_parameter->pa_list) ; cur != NULL ;
            cur = clist_next(cur)) {
            struct mailimap_single_body_fld_param * imap_param;
            
            imap_param = (struct mailimap_single_body_fld_param *) clist_content(cur);
            if (strcasecmp(imap_param->pa_name, "name") == 0) {
                if (filename() == NULL) {
                    setFilename(String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
                }
            } else if (strncasecmp(imap_param->pa_name, "name*", 5) == 0) {
                if (filename() == NULL) {
                    setFilename(String::stringByDecodingMIMEHeaderValueRfc2231(imap_param->pa_value));
                }
            } else if (strcasecmp(imap_param->pa_name, "charset") == 0) {
                setCharset(String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
            } else {
                setContentTypeParameter(String::stringWithUTF8Characters(imap_param->pa_name),
                                        String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
            }
        }
    }
}

void AbstractPart::importIMAPFields(struct mailimap_body_type_mpart * mpart) {
    struct mailimap_body_ext_mpart * bd_ext_mpart = mpart->bd_ext_mpart;
    if (bd_ext_mpart == NULL) {
        return;
    }
    mailimap_body_fld_param * parameters = bd_ext_mpart->bd_parameter;
    if (bd_ext_mpart->bd_disposition != NULL) {
        if (strcasecmp(bd_ext_mpart->bd_disposition->dsp_type, "inline") == 0) {
            setInlineAttachment(true);
        }
        else if (strcasecmp(bd_ext_mpart->bd_disposition->dsp_type, "attachment") == 0) {
            setAttachment(true);
        }
        mailimap_body_fld_param * bd_parameter = bd_ext_mpart->bd_disposition->dsp_attributes;
        if (bd_parameter != NULL) {
           clistiter * cur;
           for(cur = clist_begin(bd_parameter->pa_list) ; cur != NULL ;
               cur = clist_next(cur)) {
               struct mailimap_single_body_fld_param * imap_param;
               
               imap_param = (struct mailimap_single_body_fld_param *) clist_content(cur);
               if (strcasecmp(imap_param->pa_name, "name") == 0) {
                   if (filename() == NULL) {
                       setFilename(String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
                   }
               } else if (strncasecmp(imap_param->pa_name, "name*", 5) == 0) {
                   if (filename() == NULL) {
                       setFilename(String::stringByDecodingMIMEHeaderValueRfc2231(imap_param->pa_value));
                   }
               } else if (strcasecmp(imap_param->pa_name, "charset") == 0) {
                   setCharset(String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
               } else {
                   setContentTypeParameter(String::stringWithUTF8Characters(imap_param->pa_name),
                                           String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
               }
           }
        }
    }
    
    if (bd_ext_mpart->bd_parameter != NULL) {
        clistiter * cur;
        for(cur = clist_begin(bd_ext_mpart->bd_parameter->pa_list) ; cur != NULL ;
            cur = clist_next(cur)) {
            struct mailimap_single_body_fld_param * imap_param;

            imap_param = (struct mailimap_single_body_fld_param *) clist_content(cur);
            if (strcasecmp(imap_param->pa_name, "name") == 0) {
               if (filename() == NULL) {
                   setFilename(String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
               }
            } else if (strncasecmp(imap_param->pa_name, "name*", 5) == 0) {
               if (filename() == NULL) {
                   setFilename(String::stringByDecodingMIMEHeaderValueRfc2231(imap_param->pa_value));
               }
            } else if (strcasecmp(imap_param->pa_name, "charset") == 0) {
               setCharset(String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
            } else {
               setContentTypeParameter(String::stringWithUTF8Characters(imap_param->pa_name),
                                       String::stringByDecodingMIMEHeaderValue(imap_param->pa_value));
            }
        }
    }
}

AbstractPart * AbstractPart::partForContentID(String * contentID)
{
    if (contentID->isEqual(mContentID)) {
        return this;
    }
    else {
        return NULL;
    }
}

AbstractPart * AbstractPart::partForUniqueID(String * uniqueID)
{
    if (uniqueID->isEqual(mUniqueID)) {
        return this;
    }
    else {
        return NULL;
    }
}

String * AbstractPart::decodedStringForData(Data * data)
{
    String *lowerMimeType = mMimeType ? mMimeType->lowercaseString() : NULL;
    
    if (lowerMimeType && lowerMimeType->hasPrefix(MCSTR("text/"))) {
        bool isHTML = lowerMimeType->isEqual(MCSTR("text/html"));
        return data->stringWithDetectedCharset(mCharset, isHTML);
    }
    else {
        return NULL;
    }
}

void AbstractPart::applyUniquePartID()
{
    Array * queue = new Array();
    queue->addObject(this);
    unsigned int queueIndex = 0;
    unsigned int identifier = 0;
    while (queueIndex < queue->count()) {
        AbstractPart * part = (AbstractPart *) queue->objectAtIndex(queueIndex);
        switch (part->partType()) {
            case PartTypeSingle:
                part->setUniqueID(String::stringWithUTF8Format("%u", identifier));
                identifier ++;
                break;
            case PartTypeMessage:
                queue->addObject(((AbstractMessagePart *) part)->mainPart());
                break;
            case PartTypeMultipartMixed:
            case PartTypeMultipartRelated:
            case PartTypeMultipartAlternative:
            case PartTypeMultipartSigned:
                queue->addObjectsFromArray(((AbstractMultipart *) part)->parts());
                break;
        }
        queueIndex ++;
    }
    queue->release();
}

HashMap * AbstractPart::serializable()
{
    HashMap * result = Object::serializable();
    
    if (uniqueID() != NULL) {
        result->setObjectForKey(MCSTR("uniqueID"), uniqueID());
    }
    if (filename() != NULL) {
        result->setObjectForKey(MCSTR("filename"), filename());
    }
    if (mimeType() != NULL) {
        result->setObjectForKey(MCSTR("mimeType"), mimeType());
    }
    if (charset() != NULL) {
        result->setObjectForKey(MCSTR("charset"), charset());
    }
    if (contentID() != NULL) {
        result->setObjectForKey(MCSTR("contentID"), contentID());
    }
    if (contentLocation() != NULL) {
        result->setObjectForKey(MCSTR("contentLocation"), contentLocation());
    }
    if (contentDescription() != NULL) {
        result->setObjectForKey(MCSTR("contentDescription"), contentDescription());
    }
    if (mInlineAttachment) {
        result->setObjectForKey(MCSTR("inlineAttachment"), MCSTR("1"));
    }
    if (mAttachment) {
        result->setObjectForKey(MCSTR("attachment"), MCSTR("1"));
    }
    String * partTypeStr;
    switch (mPartType) {
        default:
        case PartTypeSingle:
            partTypeStr = MCSTR("single");
            break;
        case PartTypeMessage:
            partTypeStr = MCSTR("message");
            break;
        case PartTypeMultipartMixed:
            partTypeStr = MCSTR("multipart/mixed");
            break;
        case PartTypeMultipartRelated:
            partTypeStr = MCSTR("multipart/related");
            break;
        case PartTypeMultipartAlternative:
            partTypeStr = MCSTR("multipart/alternative");
            break;
        case PartTypeMultipartSigned:
            partTypeStr = MCSTR("multipart/signed");
            break;
    }
    result->setObjectForKey(MCSTR("partType"), partTypeStr);
    
    String * encodingString;
    switch (mEncoding) {
        case Encoding7Bit:
            encodingString = MCSTR("7bit");
            break;
        case Encoding8Bit:
        default:
            encodingString = MCSTR("8bit");
            break;
        case EncodingBinary:
            encodingString = MCSTR("binary");
            break;
        case EncodingBase64:
            encodingString = MCSTR("base64");
            break;
        case EncodingQuotedPrintable:
            encodingString = MCSTR("quoted-printable");
            break;
        case EncodingUUEncode:
            encodingString = MCSTR("uuencode");
            break;
    }
    result->setObjectForKey(MCSTR("encoding"), encodingString);
    String * sizeString = String::stringWithUTF8Format("%lu", size());
    result->setObjectForKey(MCSTR("size"), sizeString);
    return result;
}

void AbstractPart::importSerializable(HashMap * serializable)
{
    setUniqueID((String *) serializable->objectForKey(MCSTR("uniqueID")));
    setFilename((String *) serializable->objectForKey(MCSTR("filename")));
    setMimeType((String *) serializable->objectForKey(MCSTR("mimeType")));
    setCharset((String *) serializable->objectForKey(MCSTR("charset")));
    setContentID((String *) serializable->objectForKey(MCSTR("contentID")));
    setContentLocation((String *) serializable->objectForKey(MCSTR("contentLocation")));
    setContentDescription((String *) serializable->objectForKey(MCSTR("contentDescription")));
    String * value = (String *) serializable->objectForKey(MCSTR("inlineAttachment"));
    if (value != NULL) {
        if (value->intValue()) {
            setInlineAttachment(true);
        }
    }
    value = (String *) serializable->objectForKey(MCSTR("attachment"));
    if (value != NULL) {
        if (value->intValue()) {
            setAttachment(true);
        }
    }
    value = (String *) serializable->objectForKey(MCSTR("partType"));
    if (value != NULL) {
        if (value->isEqual(MCSTR("single"))) {
            setPartType(PartTypeSingle);
        }
        else if (value->isEqual(MCSTR("message"))) {
            setPartType(PartTypeMessage);
        }
        else if (value->isEqual(MCSTR("multipart/mixed"))) {
            setPartType(PartTypeMultipartMixed);
        }
        else if (value->isEqual(MCSTR("multipart/related"))) {
            setPartType(PartTypeMultipartRelated);
        }
        else if (value->isEqual(MCSTR("multipart/alternative"))) {
            setPartType(PartTypeMultipartAlternative);
        }
        else if (value->isEqual(MCSTR("multipart/signed"))) {
            setPartType(PartTypeMultipartSigned);
        }
    }
    value = (String *) serializable->objectForKey(MCSTR("encoding"));
    if (value != NULL) {
        Encoding encoding = Encoding8Bit;
        if (value->isEqual(MCSTR("7bit"))) {
            encoding = Encoding7Bit;
        }
        else if (value->isEqual(MCSTR("8bit"))) {
            encoding = Encoding8Bit;
        }
        else if (value->isEqual(MCSTR("binary"))) {
            encoding = EncodingBinary;
        }
        else if (value->isEqual(MCSTR("base64"))) {
            encoding = EncodingBase64;
        }
        else if (value->isEqual(MCSTR("quoted-printable"))) {
            encoding = EncodingQuotedPrintable;
        }
        else if (value->isEqual(MCSTR("uuencode"))) {
            encoding = EncodingUUEncode;
        }
        setEncoding(encoding);
    }
    value = (String *) serializable->objectForKey(MCSTR("size"));
    if (value != NULL) {
        setSize(value->unsignedIntValue());
    }
}

void AbstractPart::setContentTypeParameters(HashMap * parameters)
{
    MC_SAFE_REPLACE_COPY(HashMap, mContentTypeParameters, parameters);
}

Array * AbstractPart::allContentTypeParametersNames()
{
    if (mContentTypeParameters == NULL) {
        return Array::array();
    }
    return mContentTypeParameters->allKeys();
}

void AbstractPart::setContentTypeParameter(String * name, String * object)
{
    if (mContentTypeParameters == NULL) {
        mContentTypeParameters = new HashMap();
    }
    removeContentTypeParameter(name);
    mContentTypeParameters->setObjectForKey(name, object);
}

void AbstractPart::removeContentTypeParameter(String * name)
{
    if (mContentTypeParameters == NULL) {
        return;
    }
    mc_foreachhashmapKey(String, key, mContentTypeParameters) {
        if (key->isEqualCaseInsensitive(name)) {
            mContentTypeParameters->removeObjectForKey(key);
            break;
        }
    }
}

String * AbstractPart::contentTypeParameterValueForName(String * name)
{
    String * result = NULL;
    mc_foreachhashmapKey(String, key, mContentTypeParameters) {
        if (key->isEqualCaseInsensitive(name)) {
            result = (String *) mContentTypeParameters->objectForKey(key);
        }
    }
    return result;
}

void AbstractPart::setEncoding(Encoding encoding)
{
    mEncoding = encoding;
}

Encoding AbstractPart::encoding()
{
    return mEncoding;
}

void AbstractPart::setSize(unsigned int size)
{
    mSize = size;
}

unsigned int AbstractPart::size()
{
    return mSize;
}

unsigned int AbstractPart::decodedSize()
{
    switch (mEncoding) {
        case MAILIMAP_BODY_FLD_ENC_BASE64:
            return mSize * 3 / 4;
            
        default:
            return mSize;
    }
}
