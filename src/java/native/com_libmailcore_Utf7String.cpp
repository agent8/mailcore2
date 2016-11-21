#include "com_libmailcore_Utf7String.h"

#include "TypesUtils.h"
#include "JavaHandle.h"
#include "MCDefines.h"
#include "MCUtf7String.h"

using namespace mailcore;

#define nativeType Utf7String
#define javaType nativeType

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_encodeMutf7
  (JNIEnv * env, jclass cls, jstring src)
{
    MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jencodeMutf7(MC_FROM_JAVA(String, src)));
    MC_POOL_END;
    return (jstring)result;
}

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_decodeMutf7
  (JNIEnv * env, jclass cls, jstring src)
{
    MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jdecodeMutf7(MC_FROM_JAVA(String, src)));
    MC_POOL_END;
    return (jstring)result; 
}

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_flattenHTML
  (JNIEnv * env, jclass cls, jstring src)
{
	MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jflattenHTML(MC_FROM_JAVA(String, src)));
    MC_POOL_END;
    return (jstring)result; 
}

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_transferEncodingDecode
  (JNIEnv * env, jclass cls, jbyteArray data, jint encoding, jstring charset, jboolean isHtml)
{
    MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jtransferEncodingDecode(MC_FROM_JAVA(Data, data), \
      (uint32_t)encoding,MC_FROM_JAVA(String, charset),(bool)isHtml));
    MC_POOL_END;
    return (jstring)result; 
}

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_encodeRFC822Str
  (JNIEnv * env, jclass cls, jstring src)
{
    MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jencodeRFC822Str(MC_FROM_JAVA(String, src)));
    MC_POOL_END;
    return (jstring)result; 
}

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_decodeRFC822Str
  (JNIEnv * env, jclass cls, jstring src)
{
    MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jdecodeRFC822Str(MC_FROM_JAVA(String, src)));
    MC_POOL_END;
    return (jstring)result; 
}

JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_htmlEncodedString
  (JNIEnv * env, jclass cls, jstring src)
{
    MC_POOL_BEGIN;
    jobject result = MC_TO_JAVA(Utf7String::jhtmlEncodedString(MC_FROM_JAVA(String, src)));
    MC_POOL_END;
    return (jstring)result; 
}

JNIEXPORT void JNICALL Java_com_libmailcore_Utf7String_setupCode
  (JNIEnv *, jclass)
  {
      MC_POOL_BEGIN;
      Utf7String::setupCode();
      MC_POOL_END;
      return;
  }
