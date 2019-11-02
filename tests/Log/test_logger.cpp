//
// Created by tabis on 10/10/2019.
//

#include "Logger.hpp"
#include <gtest/gtest.h>

TEST(LoggerTests, debugMessageOnStdout)
{
	Debug::Logger *log = Debug::Logger::getInstance(Debug::STANDARD, Debug::Flags::fatal_off);
    testing::internal::CaptureStdout();
    std::string output;

	log->generateDebugMessage(Debug::DEBUG, "debug message", "test::debugMessageOnStdout");

	std::this_thread::sleep_for(std::chrono::seconds(1));
    output = testing::internal::GetCapturedStdout();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("\033[m[Debug]\033[0;36m debug message\033[m in \033[0;35mtest::debugMessageOnStdout\033[m\n", str.c_str());
}

TEST(LoggerTests, debugMessageInFile)
{
	Debug::Logger *log = Debug::Logger::getInstance("output.txt");
    std::string output;

 	log->generateDebugMessage(Debug::INFO, "Info message", "test::debugMessageInFile");

	std::this_thread::sleep_for(std::chrono::seconds(1));
    std::fstream stream("output.txt", std::fstream::in);
    if (!stream.is_open() || !getline(stream, output)) {
        ASSERT_NO_FATAL_FAILURE("File could not open");
        return;
    }
    stream.close();
    std::size_t pos = output.find(")");
    std::string str = output.substr(pos + 2);
    ASSERT_STREQ("[Info] Info message in test::debugMessageInFile", str.c_str());
}