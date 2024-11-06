#pragma once

#include <algorithm>
#include <string>
#include <unordered_set>
#include <iomanip>
#include <sstream>

namespace strutils
{
    inline bool is_tab_or_newline(char c) 
    {
       return (c == '\t') || (c == '\v') || (c == '\n');
    }

    inline std::string rstrip_non_printable(const std::string& input)
    {
        // Find the last printable character (starting from the back)
        auto it_end = std::find_if(input.rbegin(), input.rend(), [](char c) { 
            return std::isprint(c) && !std::isspace(c) && !is_tab_or_newline(c); }).base();

        // Return the substring between the start and last printable characters (exclusive)
        return std::string(input.begin(), it_end);
    }

    inline std::string lstrip_non_printable(const std::string& input)
    {
        // Find the first printable character (if any)
        auto it = std::find_if(input.begin(), input.end(), [](char c) { 
            return std::isprint(c) && !std::isspace(c) && !is_tab_or_newline(c); });

        // If no printable characters found, return empty string
        if (it == input.end()) {
            return "";
        }

        // Return the substring between the first printable character and the end
        return std::string(it, input.end());
    }

    inline std::string strip_non_printable(const std::string& input) 
    {
        std::string output = lstrip_non_printable(input);
        return rstrip_non_printable(output);
    }

    inline std::string to_lowercase(const std::string& input)
    {
        std::string lower_case_string = input;
        std::transform(lower_case_string.begin(), lower_case_string.end(), lower_case_string.begin(),
                    [](unsigned char c) { return std::tolower(c); });
        return lower_case_string;
    }

    inline std::string to_uppercase(const std::string& input)
    {
        std::string upper_case_string = input;
        std::transform(upper_case_string.begin(), upper_case_string.end(), upper_case_string.begin(),
                    [](unsigned char c) { return std::toupper(c); });
        return upper_case_string;
    }

    inline bool needs_hex_encoding(char c) 
    {
        static const std::unordered_set<char> invalidChars = {
            '<', '>', ':', '"', '/', '\\', '|', '?', '*', ' ', '\t', '\n', '&'
        };
        return invalidChars.find(c) != invalidChars.end();
    }

    inline std::string hex_encode_filename(const std::string& input) 
    {
        std::ostringstream hexStream;
        hexStream << std::hex << std::setfill('0'); // Set the stream to hex and fill with '0'
        
        for (unsigned char c : input) {
            if (needs_hex_encoding(c)) 
            {
                hexStream << '%' << std::setw(2) << static_cast<int>(c); // Hex-encode character
            } 
            else 
            {
                hexStream << c; // Append character as is
            }
        }
        
        return hexStream.str();
    }
}

