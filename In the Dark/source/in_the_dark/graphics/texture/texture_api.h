#pragma once
#include "external/GL/glew.h"
#include "external/glm/vec2.hpp"

namespace itd::graphics
{
	class TextureAPI
	{
	public:
		virtual ~TextureAPI() = default;

	public:
		static void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

	public:
		virtual void bind(unsigned int _active_index = 0) = 0;
		virtual void set_smooth(bool _smooth) = 0;
		virtual void set_repeat(bool _repeat) = 0;
		virtual glm::vec2 size() const = 0;
		virtual unsigned int native() const = 0;
	};
}