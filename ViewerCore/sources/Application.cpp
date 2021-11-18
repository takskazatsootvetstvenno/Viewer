#include "Application.h"
#include "Window.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include <sstream>
#include <algorithm>
#include "Game.h"
namespace TestEngine
{
	std::string stringTrim(std::string& str)
	{
		size_t start = str.find_first_not_of(" ");
		if (start == std::string::npos)
			return str;
		size_t end = str.find_last_not_of(" ");
		return str.substr(start, end - start + 1);
	}
Application::Application()
{
	LogManager::Info() << "App created!\n"<< LogManager::Show();
}

Application::~Application()
{
	LogManager::Info() << "App destroed!\n" << LogManager::Show();
}
int Application::start(const unsigned int width, const unsigned int height, std::string title)
{
	m_pWindow = std::make_unique<Window>(width, height, std::move(title));

	m_event_dispather.add_event_listener <EventCommandInput>(
		[&](EventCommandInput& event)
		{
			if(event.command.empty()) return;
			std::string command = stringTrim(event.command);
			LogManager::Command() << command << LogManager::Endl() << LogManager::Show();

			std::for_each(command.begin(), command.end(), 
				[](char& c) {c = std::toupper(c);}
			);
			std::vector<std::string> arguments;
			bool isRecognized = false;
			std::istringstream ist(command);
			std::string tempArg;
			ist >> tempArg;
			while (ist >> tempArg)
				arguments.push_back(tempArg);
			command.shrink_to_fit();
			if (command == "EXIT")
			{
				LogManager::Info() << "Exit program" << LogManager::Show();
				m_bCloseWindow = true;
				isRecognized = true;
			}
			if (command.substr(0, 3) == "SET")
			{
				if (arguments.size() == 2) {
					int x = std::stoi(arguments[0]);
					int y = std::stoi(arguments[1]);
					if (x >= 0 && x < 6 && y >= 0 && y < 6) {
						Game::Instance().setField(std::stoi(arguments[0]), std::stoi(arguments[1]));
						LogManager::Info() << "Setting a value..." << LogManager::Endl() << LogManager::Show();
					}
					else
						LogManager::Info() << "Invalid arguments" << LogManager::Endl() << LogManager::Show();
				}
				else		
				LogManager::Info() << "Need 2 arguments!" << LogManager::Endl() << LogManager::Show();
				isRecognized = true;
			}
			if (command.substr(0, 1) == "V")
			{
				if (arguments.size() == 2) {
					int x = std::stoi(arguments[0]);
					int y = std::stoi(arguments[1]);
					if (x >= 0 && x < 6 && y >= 0 && y < 6) {
						Game::Instance().setField(std::stoi(arguments[0]), std::stoi(arguments[1]));
						LogManager::Info() << "Setting a value..." << LogManager::Endl() << LogManager::Show();
					}
					else
						LogManager::Info() << "Invalid arguments" << LogManager::Endl() << LogManager::Show();
				}
				else
					LogManager::Info() << "Need 2 arguments!" << LogManager::Endl() << LogManager::Show();
				isRecognized = true;
			}
			if (command == "CLS" || command == "CLEAR")
			{
				LogManager::Instance().get_console_string().clear();
				isRecognized = true;
			}
			if (command == "CLEAR MAP")
			{
				Game::Instance().clearFields();
				LogManager::Info() << "Map is cleared!" << LogManager::Endl() << LogManager::Show();
				isRecognized = true;
			}
			if (command == "DRAW CROSS")
			{
				Game::Instance().drawCross();
				LogManager::Info() << "Cross is drawn!" << LogManager::Endl() << LogManager::Show();
				isRecognized = true;
			}
			if (command == "HELP")
			{
				LogManager::Info() << "Only god can help you, dude!" << LogManager::Endl() << LogManager::Show();
				isRecognized = true;
			}
			if(false == isRecognized)
				LogManager::Info() << "The command \""<< command << "\" was not recognized" << LogManager::Endl() << LogManager::Show();
		}
	);

	m_event_dispather.add_event_listener <EventMouseMoved>(
		[](EventMouseMoved& event)
		{
		//	LogManager::Info() << "[MouseMoved] Mouse moved to " << event.x << " x " << event.y << LogManager::Show();
		}
	);

	m_event_dispather.add_event_listener <EventScroll>(
		[&](EventScroll& event)
		{
			//LogManager::Info() << "[Scroll] y = " << event.y << "\n"<< LogManager::Show();
			m_pWindow->addCameraDistance(static_cast<float>(event.y));
		}
	);

	m_event_dispather.add_event_listener <EventKeyPressed>(
		[&](EventKeyPressed& event)
		{
			switch (event.key)
			{
			case 81:	//Q
				m_pWindow->addCameraRotation(static_cast<float>(-0.05));
			break;
			case 69:	//E
				m_pWindow->addCameraRotation(static_cast<float>(0.05));
				break;
			}
		}
	);

	m_event_dispather.add_event_listener <EventWindowResize>(
		[](EventWindowResize& event)
		{
			LogManager::Info() << "[Resized] Changing size to " << event.width << " x " << event.height << LogManager::Show();
		}
	);
	m_event_dispather.add_event_listener <EventWindowClose>(
		[&](EventWindowClose& event)
		{
			LogManager::Info() << "[WindowClose]\n" << LogManager::Show();
			m_bCloseWindow = true;
		}
	);
	m_pWindow->set_event_callback(
		[&](BaseEvent& event)
		{
			m_event_dispather.dispatch(event);
		}
	);
	while (!m_bCloseWindow)
	{
		m_pWindow->onUpdate();
	}
	
	m_pWindow = nullptr;
	return 0;
}
}
