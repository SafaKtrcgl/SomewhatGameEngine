#include "framework/Object.h"
#include "framework/Logger.h"

namespace SomewhatGameEngine
{
	Object::Object()
		: _isDestinedToDie{ false }
	{

	}

	Object::~Object()
	{
		Logger::LogMessage("Object Destroyed");
	}

	void Object::Destroy()
	{
		_isDestinedToDie = true;
	}
}