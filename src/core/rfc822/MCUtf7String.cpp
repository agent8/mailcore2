#include <MailCore/MCBaseTypes.h>
#include "MCUtf7String.h"
#include "MCAddress.h"
#include "MCDefines.h"
#include "MCLog.h"
#include "MCData.h"
#include <unicode/ustring.h>
#include <unicode/ucnv.h>
#include <unicode/utypes.h>

using namespace mailcore;

String * Utf7String::jencodeMutf7(String * src){
	String * s = src->mUTF7EncodedString();
	return s;
}

String * Utf7String::jdecodeMutf7(String * src){
	String * s = src->mUTF7DecodedString();
	return s;
}

String * Utf7String::jflattenHTML(String * src){
	if (src != NULL)
	{
		String * srcS=mailcore::String::uniquedStringWithUTF8Characters(src->UTF8Characters());
    	String * plainTextString = srcS->flattenHTMLAndShowBlockquoteAndLink(true,false);
    	return plainTextString;
	}
	else return new String("");
}

String * Utf7String::jtransferEncodingDecode(Data * data, int encoding, String * charset, bool isHTML){
	const char * dataBytes = data->bytes();
    unsigned int length = data->length();
    const char * charsetBytes = charset->UTF8Characters();
	Data * partData = Data::dataWithBytes(dataBytes, length);
    Data * decodedData = NULL;
    if (encoding == -1) {
        decodedData = partData;
    } else {
        decodedData = partData->decodedDataUsingEncoding((Encoding)encoding);
    }
    String * charsetString;
    if (charset == NULL){
        charsetString = NULL;
    }else{
        charsetString = new String(charset);
        charsetString = (String *) charsetString->autorelease();
    }
    String * str = decodedData->stringWithDetectedCharset(charsetString, isHTML);
    return str;
}

String * Utf7String::jencodeRFC822Str(String * src){
    mailcore::String *mstr  = mailcore::String::uniquedStringWithUTF8Characters(src->UTF8Characters());
    mailcore::Address *addr = mailcore::Address::addressWithNonEncodedRFC822String(mstr);
    mailcore::String *mstr2 = addr->RFC822String();
    String * rfc822String = NULL;
    if (mstr2 != NULL) {
        rfc822String = mstr2->description();
    }
    return rfc822String;

}

String * Utf7String::jdecodeRFC822Str(String * src){
    mailcore::String *mstr  = mailcore::String::uniquedStringWithUTF8Characters(src->UTF8Characters());
    mailcore::Address *addr = mailcore::Address::addressWithRFC822String(mstr);
    mailcore::String *mstr2 = addr->nonEncodedRFC822String();
    String * utf8String = NULL;
    if (mstr2 != NULL) {
        utf8String = mstr2->description();
    }
    return utf8String;
}

String * Utf7String::jhtmlEncodedString(String * src){
	String * srcS=mailcore::String::uniquedStringWithUTF8Characters(src->UTF8Characters());
    String * htmlString = srcS->htmlEncodedString();
    return htmlString;
}

void Utf7String::setupICU4C(String * src){
    u_setDataDirectory(src->fileSystemRepresentation());
    return;
}

void Utf7String::setupCode(){
    UErrorCode err;
    err = U_ZERO_ERROR;
    UConverter * converter = ucnv_open("utf-8", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "utf-8", err);
    }
    converter = ucnv_open("us-ascii", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "us-ascii", err);
    }
    converter = ucnv_open("gbk", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "gbk", err);
    }
    converter = ucnv_open("gb18030", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "gb18030", err);
    }
    converter = ucnv_open("IMAP-mailbox-name", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "IMAP-mailbox-name", err);
    }
    converter = ucnv_open("utf-16", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "utf-16", err);
    }
    converter = ucnv_open("HZ-GB-2312", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "HZ-GB-2312", err);
    }
    converter = ucnv_open("Big5", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "Big5", err);
    }
    converter = ucnv_open("ISO-8859-2", &err); 
    if (converter == NULL) {
        MCLog("invalid charset INITIALIZE %s %i", "ISO-8859-2", err);
    }
}
static void * createObject()
{
    return new Utf7String();
}

INITIALIZE(Utf7String)
{
    Object::registerObjectConstructor("mailcore::Utf7String", &createObject);
}
