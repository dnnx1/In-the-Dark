#pragma once
#include "external/glm/mat4x4.hpp"
#include "external/glm/vec4.hpp"
#include "external/glm/vec3.hpp"
#include "external/glm/vec2.hpp"

namespace itd::graphics
{
	class ShaderAPI
	{
	public:
		virtual ~ShaderAPI() = default;

	public:
		virtual void use() = 0;
		virtual void uniform(const char* _name, const glm::mat4& _matrix, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const float& _v0, const float& _v1, const float& _v2, const float& _v3, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const glm::vec4& _v, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const float& _v0, const float& _v1, const float& _v2, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const glm::vec3& _v, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const float& _v0, const float& _v1, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const glm::vec2& _v, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const float& _v, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const int& _v, bool _use_shader = false) = 0;
		virtual void uniform(const char* _name, const unsigned int& _v, bool _use_shader = false) = 0;
	};
}