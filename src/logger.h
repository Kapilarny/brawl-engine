#ifndef LOGGER_H
#define LOGGER_H

#include "defines.h"

#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

// Disable debug and trace logging in release builds
#if BUILD_RELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

enum class LOG_LEVEL {
    FATAL = 0,
    ERROR = 1,
    WARN = 2,
    INFO = 3,
    DEBUG = 4,
    TRACE = 5
};

void log_output(LOG_LEVEL level, const char* message, ...);

#define BFATAL(message, ...) log_output(LOG_LEVEL::FATAL, message, ##__VA_ARGS__);

// TODO: Just crash the program in a more elegant way lol
#define FATAL_ERROR(msg) { BFATAL("%s -> " __FILE__ " at line %d", msg, __LINE__); *(char*)0 = 0;} // funny crash. Watch the `*(char*)0 = 0` JF Sebastien presentation on this, its hilarious

#ifndef BERROR
#define BERROR(message, ...) log_output(LOG_LEVEL::ERROR, message, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLED == 1
#define BWARN(message, ...) log_output(LOG_LEVEL::WARN, message, ##__VA_ARGS__);
#else
#define BWARN(message, ...)
#endif

#if LOG_INFO_ENABLED == 1
#define BINFO(message, ...) log_output(LOG_LEVEL::INFO, message, ##__VA_ARGS__);
#else
#define BINFO(message, ...)
#endif

#if LOG_DEBUG_ENABLED == 1
#define BDEBUG(message, ...) log_output(LOG_LEVEL::DEBUG, message, ##__VA_ARGS__);
#else
#define BDEBUG(message, ...)
#endif

#if LOG_TRACE_ENABLED == 1
#define BTRACE(message, ...) log_output(LOG_LEVEL::TRACE, message, ##__VA_ARGS__);
#else
#define BTRACE(message, ...)
#endif

#endif //LOGGER_H
