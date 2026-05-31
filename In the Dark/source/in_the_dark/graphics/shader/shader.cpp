#include <string>
#include <fstream>
#include <sstream>
#include "external/GL/glew.h"
#include "external/glm/gtc/type_ptr.hpp"
#include "in_the_dark/error.h"
#include "in_the_dark/graphics/shader/shader.h"

static bool load_source(const char* _path, std::string& _out)
{
	if (!_path) return false;

	std::ifstream file(_path);
	if (!file.is_open()) return false;

	std::stringstream ss;
	ss << file.rdbuf();
	_out = ss.str();

	file.close();
	if (_out.empty()) return false;
	return true;
}

static unsigned int generate_shader_id(const char* _src, unsigned int _type, int& _success)
{
	unsigned int id;
	id = glCreateShader(_type);
	glShaderSource(id, 1, &_src, nullptr);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &_success);
	return id;
}

itd::graphics::Shader::Shader(const char* _vert, const char* _frag)
{
	int success;
	const size_t buffer_size = 512;
	char log[buffer_size];

	unsigned int vert_shader = generate_shader_id(_vert, GL_VERTEX_SHADER, success);
	if (!success)
	{
		glGetShaderInfoLog(vert_shader, buffer_size, nullptr, log);
		glDeleteShader(vert_shader);
		std::string err("Vertex shader failed:\n");
		err += log;
		err += "\n__________\n";
		err += _vert;
		throw itd::Error("Shader", err);
	}

	unsigned int frag_shader = generate_shader_id(_frag, GL_FRAGMENT_SHADER, success);
	if (!success)
	{
		glGetShaderInfoLog(frag_shader, buffer_size, nullptr, log);
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);
		std::string err("Fragment shader failed:\n");
		err += log;
		err += "\n__________\n";
		err += _frag;
		throw itd::Error("Shader", err);
	}

	unsigned int id = glCreateProgram();
	glAttachShader(id, vert_shader);
	glAttachShader(id, frag_shader);

	glLinkProgram(id);
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(id, buffer_size, nullptr, log);
		glDeleteShader(vert_shader);
		glDeleteShader(frag_shader);
		glDeleteProgram(id);
		std::string err("Shader program failed:\n");
		err += log;
		throw itd::Error("Shader", err);
	}

	glDeleteShader(vert_shader);
	glDeleteShader(frag_shader);

	m_id = id;
}

itd::graphics::Shader::~Shader()
{
	if (m_id) glDeleteProgram(m_id);
}

std::shared_ptr<itd::graphics::Shader> itd::graphics::Shader::make_shared_from_file(const char* _vert_path, const char* _frag_path)
{
	std::string vert_buffer;
	std::string frag_buffer;
	std::string geom_buffer;

	if (!load_source(_vert_path, vert_buffer))
		throw itd::Error("Shader", "Loading vertex shader source failed");
	if (!load_source(_frag_path, frag_buffer))
		throw itd::Error("Shader", "Loading fragment shader source failed");

	return std::make_shared<Shader>(vert_buffer.c_str(), frag_buffer.c_str());
}

std::shared_ptr<itd::graphics::Shader> itd::graphics::Shader::make_shared_from_memory(const char* _vert, const char* _frag)
{
	return std::make_shared<Shader>(_vert, _frag);
}

void itd::graphics::Shader::use()
{
	glUseProgram(m_id);
}

void itd::graphics::Shader::uniform(const char* _name, const glm::mat4& _matrix, bool _use_shader)
{
	if (_use_shader) use();
	glUniformMatrix4fv(glGetUniformLocation(m_id, _name), 1, GL_FALSE, glm::value_ptr(_matrix));
}

void itd::graphics::Shader::uniform(const char* _name, const float& _v0, const float& _v1, const float& _v2, const float& _v3, bool _use_shader)
{
	if (_use_shader) use();
	glUniform4f(glGetUniformLocation(m_id, _name), _v0, _v1, _v2, _v3);
}

void itd::graphics::Shader::uniform(const char* _name, const glm::vec4& _v, bool _use_shader)
{
	uniform(_name, _v.x, _v.y, _v.z, _v.w, _use_shader);
}

void itd::graphics::Shader::uniform(const char* _name, const float& _v0, const float& _v1, const float& _v2, bool _use_shader)
{
	if (_use_shader) use();
	glUniform3f(glGetUniformLocation(m_id, _name), _v0, _v1, _v2);
}

void itd::graphics::Shader::uniform(const char* _name, const glm::vec3& _v, bool _use_shader)
{
	uniform(_name, _v.x, _v.y, _v.z, _use_shader);
}

void itd::graphics::Shader::uniform(const char* _name, const float& _v0, const float& _v1, bool _use_shader)
{
	if (_use_shader) use();
	glUniform2f(glGetUniformLocation(m_id, _name), _v0, _v1);
}

void itd::graphics::Shader::uniform(const char* _name, const glm::vec2& _v, bool _use_shader)
{
	uniform(_name, _v.x, _v.y, _use_shader);
}

void itd::graphics::Shader::uniform(const char* _name, const float& _v, bool _use_shader)
{
	if (_use_shader) use();
	glUniform1f(glGetUniformLocation(m_id, _name), _v);
}

void itd::graphics::Shader::uniform(const char* _name, const int& _v, bool _use_shader)
{
	if (_use_shader) use();
	glUniform1i(glGetUniformLocation(m_id, _name), _v);
}

void itd::graphics::Shader::uniform(const char* _name, const unsigned int& _v, bool _use_shader)
{
	if (_use_shader) use();
	glUniform1ui(glGetUniformLocation(m_id, _name), _v);
}
