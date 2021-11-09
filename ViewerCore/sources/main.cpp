#include"LogManager.h"
#include<memory>
#include"Application.h"


int main()
{
#if CMAKE_BUILD_TYPE_RELEASE
	TestEngine::LogManager::Info() << "This is RELEASE solution\n" << TestEngine::LogManager::Show();
#else
	TestEngine::LogManager::Info() << "This is DEBUG solution\n" << TestEngine::LogManager::Show();
#endif
#ifdef _WIN32 
	TestEngine::LogManager::Info() << "Running on Windos OS\n" << TestEngine::LogManager::Show();
#elif __unix__ 
	TestEngine::LogManager::Info() << "Running on Unix OS\n" << TestEngine::LogManager::Show();
#elif __linux__
	TestEngine::LogManager::Info() << "Running on Linux OS\n" << TestEngine::LogManager::Show();
#endif 

	auto App = std::make_unique<TestEngine::Application>();
	int returnCode = App->start(1280, 720, "test1");
	//system("pause");
	return returnCode;
}