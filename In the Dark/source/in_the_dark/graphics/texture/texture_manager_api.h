#pragma once
#include <memory>
#include <string>
#include "in_the_dark/graphics/texture/texture_api.h"

namespace itd::graphics
{
	class TextureManagerAPI
	{
	public:
		virtual ~TextureManagerAPI() = default;

	public:
		virtual void add(std::string _name, std::shared_ptr<TextureAPI> _texture) = 0;
		virtual std::shared_ptr<TextureAPI> get(std::string _name) = 0;
	};
}