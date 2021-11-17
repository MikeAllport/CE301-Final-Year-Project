#include "gepch.h"
#include "Logger.h"

std::shared_ptr<spdlog::logger> Logger::l;
bool Logger::initialized = false;

void Logger::init()
{
	spdlog::set_pattern("%^[%D %r] %n: %v%$");
	l = spdlog::stdout_color_mt("GE");
	l->set_level(spdlog::level::trace);
	initialized = true;
}

std::shared_ptr<spdlog::logger>& Logger::getInstance()
{
	if (!initialized) init();
	return l;
};
