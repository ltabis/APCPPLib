/*
 *
 *   Lucas Tabis
 *   Logger class source file
 *
 *
 */

#include "Logger.hpp"


/*
 *   Construcor / Destructor.
 */

Debug::Logger::Logger(mode mode) : _mode(mode), _file("output.txt") {}
Debug::Logger::~Logger() {}


void Debug::Logger::switchMode(mode mode, const std::string &filePath)
{
    if (_mode == mode)
        return;
    _mode = mode;
    if (mode == FILE)
        _file.open(filePath.empty() ? DEFAULT_LOG_FILE : filePath, std::ios::app);
    else
        if (_file.is_open())
            _file.close();
}

/*
 *   generate a debug message with a type and where parameters.
 */

void Debug::Logger::generateDebugMessage(type type, const std::string &message, const std::string &where)
{
    if (_mode == OFF)
        return;
    else if (_mode == STANDARD)
        generateMessageOnStandardOutput(type, message, where);
    else if (_mode == FILE)
        generateMessageInFile(type, message, where);
}

void Debug::Logger::generateMessageInFile(type type, const std::string &message, const std::string &where)
{
    _file << getMessageFromType(type) << " " << message <<  " in " << where;
}

void Debug::Logger::generateMessageOnStandardOutput(type type, const std::string &message, const std::string &where)
{
    std::cout << getMessageColorFromType(type) << getMessageFromType(type) << " " << CYAN << message << WHITE <<  " in " << MAGENTA << where << WHITE << std::endl;
}