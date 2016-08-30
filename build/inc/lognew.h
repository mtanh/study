#ifndef LOGNEW_H_
#define LOGNEW_H_

enum LogLevel { LOG_DEBUG, LOG_TRACE, LOG_INFO, LOG_ERROR };

extern void LogPrintf( char *msg, LogLevel level );

#endif