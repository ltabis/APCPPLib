//
// Created by tabis on 09/10/2019.
//

#include "Exception.hpp"

Log::Exception::~Exception() = default;

void Log::Exception::debugErrorMessage()
{
    std::cerr << RED << "[Exception] " << MAGENTA << _what << WHITE << " in method " << BLUE << _where << std::endl;
}

Log::Exception::Exception(const std::string &what, const std::string &where) : _what(what), _where(where) {}
Log::Exception::Exception(const char *what, const char *where) : _what(what), _where(where) {}
