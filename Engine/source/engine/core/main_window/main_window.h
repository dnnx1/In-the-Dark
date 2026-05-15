#pragma once
#include <memory>
#include <queue>
#include "external/GLFW/glfw3.h"
#include "engine/core/event.h"
#include "engine/core/main_window/main_window_api.h"

namespace itd::core
{
	class MainWindow : public MainWindowAPI
	{
	public:
		struct CreationInfo
		{
			int width{ 0 };
			int height{ 0 };
			const char* title{ nullptr };
		};

	private:
		using GLFWwindowPtr = std::unique_ptr<GLFWwindow, void(*)(GLFWwindow*)>;

	public:
		MainWindow(const CreationInfo& _info);
		~MainWindow();

		MainWindow(const MainWindow&) = delete;
		MainWindow(MainWindow&&) = delete;

		MainWindow& operator=(const MainWindow&) = delete;
		MainWindow& operator=(MainWindow&&) = delete;

	public:
		static std::unique_ptr<MainWindow> make_unique(int _width, int _height, const char* _title);

	public:
		template <typename Func> inline void poll_events(Func&& _func)
		{
			glfwPollEvents();
			while (!m_events.empty())
			{
				auto evt = std::move(m_events.front());
				m_events.pop();
				_func(evt);
			}
		}

	public:
		void set_should_close(bool _close);
		bool should_close() const;

		void set_position(glm::ivec2 _pos);
		void set_position(int _x, int _y);
		glm::ivec2 position() const override;

		void set_size(glm::ivec2 _size);
		void set_size(int _width, int _height);
		glm::ivec2 size() const override;

		glm::ivec2 framebuffer_size() const override;

		bool iconified() const override;
		bool maximized() const override;
		bool focused() const override;

		void set_mode(Mode _mode);
		Mode mode() const override;

	private:
		void setup_callbacks();

	private:
		GLFWwindowPtr m_glfw_window{ nullptr, glfwDestroyWindow };
		std::queue<Event> m_events;

		glm::ivec2 m_windowed_position{ 0 };
		glm::ivec2 m_windowed_size{ 0 };
		Mode m_mode{ Mode::Windowed };
	};
}