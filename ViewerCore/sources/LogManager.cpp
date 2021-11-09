
#include "LogManager.h"
#include <ctime>
#include <iostream>
namespace TestEngine {
	LogManager& LogManager::operator<<(const std::string& s)
	{
		m_buffer_string += s;
		return *this;
	}
	LogManager& LogManager::operator<<(const MessageCommand& command)
	{
		switch (command)
		{
		case MessageCommand::Show:
			switch (ManagerConsoleOutput)
			{
			case TestEngine::ConsoleType::Cout:
				std::cout << m_buffer_string;
				m_buffer_string.clear();
				break;
			case TestEngine::ConsoleType::Console:
				std::cout << m_buffer_string;
				m_console_string += m_buffer_string;
				m_buffer_string.clear();
				break;
			}
			m_console_string_changed = true;
		case MessageCommand::Endl:
			m_buffer_string += '\n';
			break;
		}
		return *this;
	}
	LogManager& LogManager::operator<<(const MessageType& type)
	{
		if (is_time_draw){
			time_t now = time(0);
			tm ltm;
			//localtime_r(&ltm, &now);
			//m_buffer_string += std::to_string(ltm.tm_hour) + ":" + std::to_string(ltm.tm_min) + ":" + std::to_string(ltm.tm_sec) + " ";
            m_buffer_string += "Time is subjective| ";
		}
		switch (type)
		{
		case MessageType::Debug:
			m_buffer_string += "time";
			break;
		case MessageType::Error:
			m_buffer_string += "Error: ";
			break;
		case MessageType::Info:
			m_buffer_string += "Info: ";
			break;
		}
		return *this;
	}
	LogManager& LogManager::Error()
	{
		return LogManager::Instance() << MessageType::Error;
	}
	LogManager& LogManager::Info()
	{
		return LogManager::Instance() << MessageType::Info;
	}
	LogManager& LogManager::Debug()
	{
		return LogManager::Instance() << MessageType::Debug;
	}
	LogManager& LogManager::Command()
	{
		return LogManager::Instance();
	}
	MessageCommand LogManager::Show()
	{
		return MessageCommand::Show;
	}
}