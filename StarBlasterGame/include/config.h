#pragma once
#include <string>

std::string GetResourceDirectory()
{
#ifdef NDEBUG
	return "assets/";
#else
	return "C:/SomewhatGameEngine/SomewhatGameEngine/StarBlasterGame/assets/";
#endif
}
