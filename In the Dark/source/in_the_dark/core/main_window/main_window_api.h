#pragma once
#include "external/glm/vec2.hpp"

namespace itd::core
{
	class MainWindowAPI
	{
	public:
		enum class Mode : uint8_t
		{
			Windowed,
			Borderless,
			Fullscreen,
		};

	public:
		virtual ~MainWindowAPI() = default;

	public:
		virtual glm::ivec2 position() const = 0;
		virtual glm::ivec2 size() const = 0;
		virtual glm::ivec2 framebuffer_size() const = 0;
		virtual bool iconified() const = 0;
		virtual bool maximized() const = 0;
		virtual bool focused() const = 0;
		virtual Mode mode() const = 0;
	};
}