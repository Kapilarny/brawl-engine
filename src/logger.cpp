#include "logger.h"

// TODO: Make this platform-independent && stdlib independent
#include <stdarg.h>
#include <windows.h>
#include <string>

#include "memory/bmemory.h"

void log_output(LOG_LEVEL level, const char *message, ...) {
    const char* level_strings[6] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    const u8 level_colors[6] = {64, 4, 6, 2, 1, 8};

    char out_message[5000]; // 5k should be enough for a single log message TODO: make this dynamic
    bzero_memory(out_message, sizeof(out_message));

    // Format message
    va_list args;
    va_start(args, message);
    vsprintf(out_message, message, args);
    va_end(args);

    char final_message[5000]; // 5k should be enough for a single log message TODO: make this dynamic
    bzero_memory(final_message, sizeof(final_message));

    // Add level string
    strcat(final_message, level_strings[(int)level]);

    // Add message
    strcat(final_message, out_message);

    // Add newline
    strcat(final_message, "\n");

    // Set console color TODO: make this platform-independent
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, level_colors[(u32)level]);

    WriteConsoleA(hConsole, final_message, strlen(final_message), NULL, NULL);
}
