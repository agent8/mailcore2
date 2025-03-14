/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_libmailcore_Utf7String */

#ifndef _Included_com_libmailcore_Utf7String
#define _Included_com_libmailcore_Utf7String
#ifdef __cplusplus
extern "C" {
#endif
#undef com_libmailcore_Utf7String_serialVersionUID
#define com_libmailcore_Utf7String_serialVersionUID 1LL
#undef com_libmailcore_Utf7String_serialVersionUID
#define com_libmailcore_Utf7String_serialVersionUID 1LL
/*
 * Class:     com_libmailcore_Utf7String
 * Method:    encodeMutf7
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_encodeMutf7
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    decodeMutf7
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_decodeMutf7
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    flattenHTML
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_flattenHTML
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    transferEncodingDecode
 * Signature: ([BILjava/lang/String;Z)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_transferEncodingDecode
  (JNIEnv *, jclass, jbyteArray, jint, jstring, jboolean);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    encodeRFC822Str
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_encodeRFC822Str
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    decodeRFC822Str
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_decodeRFC822Str
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    htmlEncodedString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_libmailcore_Utf7String_htmlEncodedString
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    setupCode
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_Utf7String_setupCode
  (JNIEnv *, jclass);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    setupICU4C
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_Utf7String_setupICU4C
  (JNIEnv *, jclass, jstring);

/*
 * Class:     com_libmailcore_Utf7String
 * Method:    setupNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_Utf7String_setupNative
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
