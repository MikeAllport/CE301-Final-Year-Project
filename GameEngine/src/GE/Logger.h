#ifndef GE_LOGGER
#define GE_LOGGER

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

/**
* Logger's purpose is to provide functionality to output color coded messages to the console
* dependant on message type through use of spdlog. This is facilitated through use of macros
* Logger is a singleton class
*/
// Code adapted from
// https://github.com/TheCherno/Hazel
class Logger
{
public:
	static std::shared_ptr<spdlog::logger>& getInstance();
private:
	static void init();
	static std::shared_ptr<spdlog::logger> l;
	static bool initialized;
};

// console message macros
#define GE_ERROR(...)		Logger::getInstance()->error(__VA_ARGS__)
#define GE_WARN(...)		Logger::getInstance()->warn(__VA_ARGS__)
#define GE_INFO(...)		Logger::getInstance()->info(__VA_ARGS__)
#define GE_FATAL(...)		Logger::getInstance()->critical(__VA_ARGS__)

#endif // !GE_LOGGER
