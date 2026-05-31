#pragma once
#include <memory>
#include "in_the_dark/graphics/shader/shader_api.h"

namespace itd::graphics
{
	class Shader : public ShaderAPI
	{
	public:
		Shader(const char* _vert, const char* _frag);
		~Shader();

		Shader(const Shader&) = delete;
		Shader(Shader&&) = delete;

		Shader& operator=(const Shader&) = delete;
		Shader& operator=(Shader&&) = delete;

	public:
		static std::shared_ptr<Shader> make_shared_from_file(const char* _vert_path, const char* _frag_path);
		static std::shared_ptr<Shader> make_shared_from_memory(const char* _vert, const char* _frag);

	public:
		void use() override;
		void uniform(const char* _name, const glm::mat4& _matrix, bool _use_shader) override;
		void uniform(const char* _name, const float& _v0, const float& _v1, const float& _v2, const float& _v3, bool _use_shader) override;
		void uniform(const char* _name, const glm::vec4& _v, bool _use_shader) override;
		void uniform(const char* _name, const float& _v0, const float& _v1, const float& _v2, bool _use_shader) override;
		void uniform(const char* _name, const glm::vec3& _v, bool _use_shader) override;
		void uniform(const char* _name, const float& _v0, const float& _v1, bool _use_shader) override;
		void uniform(const char* _name, const glm::vec2& _v, bool _use_shader) override;
		void uniform(const char* _name, const float& _v, bool _use_shader) override;
		void uniform(const char* _name, const int& _v, bool _use_shader) override;
		void uniform(const char* _name, const unsigned int& _v, bool _use_shader) override;

	private:
		unsigned int m_id{ 0 };
	};
}