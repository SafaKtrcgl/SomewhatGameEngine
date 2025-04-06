#pragma once

namespace SomewhatGameEngine
{
	class Object
	{
	public:
		Object();
		virtual ~Object();

		virtual void Destroy();
		bool IsDestinedToDie() const { return _isDestinedToDie; }
	private:
		bool _isDestinedToDie;
	};
}