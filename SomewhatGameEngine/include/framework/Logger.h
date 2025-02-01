#pragma once
#include <string>


namespace SomewhatGameEngine
{
	class Logger
	{
	public:
		static void LogMessage(std::string_view message);
	};
}