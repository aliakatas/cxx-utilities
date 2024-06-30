#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <algorithm>
//#include <cctype>
#include <string>

namespace strutils
{
    inline bool is_tab_or_newline(char c) 
    {
       return (c == '\t') || (c == '\v') || (c == '\n');
    }

    inline std::string strip_non_printable(const std::string& str) 
    {
        // Find the first printable character (if any)
        auto it = std::find_if(str.begin(), str.end(), [](char c) { 
            return std::isprint(c) && !std::isspace(c) && !is_tab_or_newline(c); });

        // If no printable characters found, return empty string
        if (it == str.end()) {
            return "";
        }

        // Find the last printable character (starting from the back)
        auto it_end = std::find_if(str.rbegin(), str.rend(), [](char c) { 
            return std::isprint(c) && !std::isspace(c) && !is_tab_or_newline(c); }).base();

        // Return the substring between the first and last printable characters (exclusive)
        return std::string(it, it_end);
    }
}

#endif // STRING_UTILS_H