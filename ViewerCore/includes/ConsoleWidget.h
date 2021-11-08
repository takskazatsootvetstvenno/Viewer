#pragma once
#include<string>
#include<functional>

namespace TestEngine {
	class BaseEvent;
	class ConsoleWidget
	{
	public:
		ConsoleWidget() {};
		~ConsoleWidget() {};
		ConsoleWidget(const ConsoleWidget&) = delete;
		ConsoleWidget(ConsoleWidget&&) = delete;
		ConsoleWidget& operator=(const ConsoleWidget&) = delete;
		ConsoleWidget& operator=(ConsoleWidget&&) = delete;
		static void drawConsoleWidget(
			const unsigned int& width,
			const unsigned int& height,
			std::function<void(BaseEvent&)>& EventCallbackFn);
	};
}
