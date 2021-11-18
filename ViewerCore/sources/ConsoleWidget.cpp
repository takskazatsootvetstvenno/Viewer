#include "ConsoleWidget.h"
#include "LogManager.h"
#include "Event.h"
#include "imgui.h"
//#include "cpp/imgui_stdlib.h"
namespace TestEngine {
/*static*/void ConsoleWidget::drawConsoleWidget(
			const unsigned int& width,
			const unsigned int& height,
			std::function<void(BaseEvent&)>& EventCallbackFn
			)
	{
		ImGui::SetNextWindowPos(ImVec2(
			width * 0.6f,
			height * 0.02f));
		ImGui::SetNextWindowSize(ImVec2(
			width * 0.39f,
			height * 0.4f));

		ImGui::Begin("Console", nullptr,
			ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoMove
		);
		if (ImGui::Button("Clear", ImVec2(-1.0f, 0.0f)))
		{
			LogManager::Instance().get_console_string().clear();
		}
		ImGui::Checkbox("Write time", &LogManager::Instance().is_time_draw);

		ImGui::Separator();

		
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, height *0.25f), false, ImGuiWindowFlags_HorizontalScrollbar);
		ImGui::TextUnformatted(LogManager::Instance().get_console_string().c_str());
		if (LogManager::Instance().m_console_string_changed)
		{
			ImGui::SetScrollHereY(1.0f);
			LogManager::Instance().m_console_string_changed = false;
		}
		ImGui::EndChild();

		std::string commandStr(30, '\0');
		ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
		if (ImGui::InputText("Input command", &commandStr[0], commandStr.size(), input_text_flags))
		{
			EventCommandInput event(commandStr.substr(0, commandStr.find_first_of('\0')));
			EventCallbackFn(event);
			ImGui::SetKeyboardFocusHere(-1);
		}
		
		ImGui::End();
	}
}