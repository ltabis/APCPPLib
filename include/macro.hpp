//
// Created by tabis on 09/10/2019.
//

#pragma once

constexpr auto const RED                =  "\033[0;31m";
constexpr auto const REDUNDERLINED      =  "\033[0;41m";
constexpr auto const GREEN              =  "\033[0;32m";
constexpr auto const YELLOW             =  "\033[0;33m";
constexpr auto const BLUE               =  "\033[0;34m";
constexpr auto const MAGENTA            =  "\033[0;35m";
constexpr auto const CYAN               =  "\033[0;36m";
constexpr auto const WHITE              =  "\033[m";

constexpr auto const DEFAULT_LOG_FILE   =  "output.txt";
constexpr auto const WARNING_MESSAGE    =  "[Warning]";
constexpr auto const ERROR_MESSAGE      =  "[Error]";
constexpr auto const DEBUG_MESSAGE      =  "[Debug]";
constexpr auto const FATAL_MESSAGE      =  "[FATAL]";
constexpr auto const INFO_MESSAGE       =  "[Info]";

// Flags options for the Logger class
namespace Debug {
    namespace Flags {
        typedef enum e_options {all_on = 1, debug_off = 2, info_off = 4, warning_off = 8, error_off = 16, fatal_off = 32} options;
    }
}
