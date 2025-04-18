/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_libmailcore_IMAPFolderInfo */

#ifndef _Included_com_libmailcore_IMAPFolderInfo
#define _Included_com_libmailcore_IMAPFolderInfo
#ifdef __cplusplus
extern "C" {
#endif
#undef com_libmailcore_IMAPFolderInfo_serialVersionUID
#define com_libmailcore_IMAPFolderInfo_serialVersionUID 1LL
/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    uidNext
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_libmailcore_IMAPFolderInfo_uidNext
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setUidNext
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setUidNext
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    uidValidity
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_libmailcore_IMAPFolderInfo_uidValidity
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setUidValidity
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setUidValidity
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    modSequenceValue
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_libmailcore_IMAPFolderInfo_modSequenceValue
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setModSequenceValue
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setModSequenceValue
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    unseenCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_libmailcore_IMAPFolderInfo_unSeenMessageCount
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setUnseenCount
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setUnSeenMessageCount
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    messageCount
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_libmailcore_IMAPFolderInfo_messageCount
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setMessageCount
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setMessageCount
  (JNIEnv *, jobject, jint);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    firstUnseenUid
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_libmailcore_IMAPFolderInfo_firstUnseenUid
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setFirstUnseenUid
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setFirstUnseenUid
  (JNIEnv *, jobject, jlong);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    allowsNewPermanentFlags
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_com_libmailcore_IMAPFolderInfo_allowsNewPermanentFlags
  (JNIEnv *, jobject);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setAllowsNewPermanentFlags
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setAllowsNewPermanentFlags
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     com_libmailcore_IMAPFolderInfo
 * Method:    setupNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_libmailcore_IMAPFolderInfo_setupNative
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
