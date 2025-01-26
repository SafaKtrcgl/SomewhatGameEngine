#include <iostream>
#include <string_view>

#include "framework/Logger.h"

namespace SomewhatGameEngine
{
	void Logger::LogMessage(std::string_view message)
	{
		std::cout << "[Message] " << message << '\n';
	}
}