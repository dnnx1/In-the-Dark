#pragma once
#include <memory>
#include <string>
#include "in_the_dark/graphics/shader/shader_api.h"

namespace itd::graphics
{
	class ShaderManagerAPI
	{
	public:
		virtual ~ShaderManagerAPI() = default;

	public:
		virtual void add(std::string _name, std::shared_ptr<ShaderAPI> _shader) = 0;
		virtual std::shared_ptr<ShaderAPI> get(std::string _name) = 0;
	};
}