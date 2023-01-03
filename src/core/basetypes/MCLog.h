#ifndef MAILCORE_MCLOG_H

#define MAILCORE_MCLOG_H

#include <stdio.h>
#include <MailCore/MCUtils.h>

//zhaoshuo:
//if log is disabled, should not calculate __VA_ARGS__ if it is a statement. like TypesUtils.cpp#arrayObjectToJavaConverter#MCUTF8(...)
//some messages can't translate to UTF8 code, and may cause crash.
#if __APPLE__
#   include "TargetConditionals.h"
#   if defined(TARGET_OS_MAC) && TARGET_OS_MAC
#       define MCLog(...) if(MCLogEnabled) MCHandleLog(__FILE__, __LINE__, __VA_ARGS__)
#   else
#       define MCLog(...) if(MCLogEnabled) MCLogInternal(NULL, __FILE__, __LINE__, 0, __VA_ARGS__)
#   endif
#else
#   define MCLog(...) if(MCLogEnabled) MCLogInternal(NULL, __FILE__, __LINE__, 0, __VA_ARGS__)
#endif

#define MCLogStack(...) if(MCLogEnabled) MCLogInternal(NULL, __FILE__, __LINE__, 1, __VA_ARGS__)
#define MCLogOutput(...) if(MCLogEnabled) MCHandleLog(__FILE__, __LINE__, __VA_ARGS__)

MAILCORE_EXPORT
extern int MCLogEnabled;
    
#ifndef __printflike
#define __printflike(a,b)
#endif

typedef void (* LogHandler)(const char * filename, unsigned int line, const char * format, va_list args);

#ifdef __cplusplus
extern "C" {
#endif
    MAILCORE_EXPORT
    void MCLogInternal(const char * user,
                       const char * filename,
                       unsigned int line,
                       int dumpStack,
                       const char * format, ...) __printflike(5, 6);

    MAILCORE_EXPORT
    void MCRegisterLogger(LogHandler handler);

    MAILCORE_EXPORT
    void MCUnregisterLogger();

    MAILCORE_EXPORT
    void MCHandleLog(const char * filename, unsigned int line, const char * format, ...);

#ifdef __cplusplus
}
#endif

#endif
