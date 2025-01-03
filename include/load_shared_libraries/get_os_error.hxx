#pragma once

#include <string>

#if defined (__WIN32__) || defined(_WIN32)
#include <windows.h>
#elif defined(__linux__)
#include <dlfcn.h>
#define Dlerror dlerror
#endif

inline std::string get_os_error() noexcept
{
#if defined (__WIN32__) || defined(_WIN32)

    DWORD error_code = GetLastError();

    // Buffer to store the error message
    TCHAR win_message[256];

    // Call FormatMessage to convert the error code to a string
    DWORD result = FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM,  // Get message from system error codes
        NULL,                          // No source string to format
        error_code,                     // The error code to convert
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
        win_message,                       // Buffer to receive the message
        sizeof(win_message) / sizeof(TCHAR) - 1,  // Size of message buffer in TCHARs
        NULL                           // No additional formatting arguments
    );

    std::string what_happened;
    if (result)
    {
#ifdef UNICODE
        std::wstring tt = std::wstring(win_message);
#else
        std::string tt = std::string(win_message);
#endif
        
        what_happened = std::string(tt.begin(), tt.end());
    }
    else
        // Handle potential formatting errors
        what_happened = std::string("Unknown error ") + std::to_string(error_code);
#elif defined(__linux__)
    std::string what_happened = std::string(Dlerror());
#endif
    return what_happened;
}

