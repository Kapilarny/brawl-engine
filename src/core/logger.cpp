#include "logger.h"

// TODO: Make this stdlib independent
#include <cstdarg>
#include <string> // vsprintf TODO: implement yourself

#include "memory/bmemory.h"
#include "memory/bstring.h"
#include "platform/platform.h"

void log_output(LOG_LEVEL level, const char *message, ...) {
    const char* level_strings[6] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};

    char out_message[5000]; // 5k should be enough for a single log message TODO: make this dynamic
    bzero_memory(out_message, sizeof(out_message));

    // Format message
    va_list args;
    va_start(args, message);
    vsprintf(out_message, message, args); // TODO: make this stdlib-independent
    va_end(args);

    char final_message[5000]; // 5k should be enough for a single log message TODO: make this dynamic
    bzero_memory(final_message, sizeof(final_message));

    // Add level string
    bstrcat(final_message, (char*)level_strings[(int)level]);

    // Add message
    bstrcat(final_message, out_message);

    // Add newline
    bstrcat(final_message, (char*)"\n");

    platform_log_output(final_message, level);
}
