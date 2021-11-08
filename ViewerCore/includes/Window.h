#pragma once
#include<string>
#include<functional>
#include"Event.h"
struct GLFWwindow;
namespace TestEngine {
	struct CameraData
	{
		float distance = 10.f;
		float rotation = 0.f;
	};
	class Window
	{
	public:
		using EventCallbackFn = std::function<void(BaseEvent&)>;
		~Window();
		Window(const unsigned int width, const unsigned int height, std::string title);
		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;
		size_t getWidth() const;
		size_t getHeight() const;
		void onUpdate();
		void addCameraDistance(float newValue);
		void addCameraRotation(float newValue);
		float getCameraDistance() const;
		float getCameraRotation() const;
		void set_event_callback(const EventCallbackFn& callback)
		{
			m_data.eventCallbackFn = callback;
		}

	private:
		struct WindowData
		{
			unsigned int m_width;
			unsigned int m_height;
			std::string m_title;
			EventCallbackFn eventCallbackFn;
		};
		void init();
		WindowData m_data;
		GLFWwindow* m_pWindow = nullptr;
		CameraData m_CameraData;
	};
}
