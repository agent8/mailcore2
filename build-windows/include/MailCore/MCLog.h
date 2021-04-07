#ifndef MAILCORE_MCLOG_H

#define MAILCORE_MCLOG_H

#include <stdio.h>
#include <MailCore/MCUtils.h>

#define MCLog(...) MCLogInternal(NULL, __FILE__, __LINE__, 0, __VA_ARGS__)
#define MCLogStack(...) MCLogInternal(NULL, __FILE__, __LINE__, 1, __VA_ARGS__)
#define MCLogOutput(...) MCHandleLog(__FILE__, __LINE__, __VA_ARGS__)

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
