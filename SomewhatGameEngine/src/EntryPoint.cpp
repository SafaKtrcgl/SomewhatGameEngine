#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
	SomewhatGameEngine::Application* application = GetApplication();
	application->Run();
	delete application;
}