#include "external/stb_image/stb_image.h"
#include "in_the_dark/error.h"
#include "in_the_dark/graphics/texture/texture.h"

static bool calc_format(int _channels, unsigned int& _format)
{
	switch (_channels)
	{
	case 1: _format = GL_RED; break;
	case 3: _format = GL_RGB; break;
	case 4: _format = GL_RGBA; break;
	default: return false;
	}
	return true;
}

itd::graphics::Texture::Texture(int _iformat, int _width, int _height, unsigned int _format, unsigned int _type, unsigned char* _pixels)
{
	unsigned int id{ 0 };
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, _iformat, _width, _height, 0, _format, _type, _pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_id = id;
	m_size = glm::vec2(_width, _height);
}

itd::graphics::Texture::~Texture()
{
	if (m_id) glDeleteTextures(1, &m_id);
}

std::shared_ptr<itd::graphics::Texture> itd::graphics::Texture::make_shared_empty(Format _format, int _width, int _height)
{
	switch (_format)
	{
	case Format::R8:		return std::make_shared<Texture>(GL_R8, _width, _height, GL_RED, GL_UNSIGNED_BYTE, nullptr);
	case Format::R16F:		return std::make_shared<Texture>(GL_R16F, _width, _height, GL_RED, GL_FLOAT, nullptr);
	case Format::RGB8:		return std::make_shared<Texture>(GL_RGB8, _width, _height, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	case Format::RGB16F:	return std::make_shared<Texture>(GL_RGB16F, _width, _height, GL_RGB, GL_FLOAT, nullptr);
	case Format::RGBA8:		return std::make_shared<Texture>(GL_RGBA8, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	case Format::RGBA16F:	return std::make_shared<Texture>(GL_RGBA16F, _width, _height, GL_RGBA, GL_FLOAT, nullptr);
	default: throw Error("Texture", "Invalid empty texture format");
	}
}

std::shared_ptr<itd::graphics::Texture> itd::graphics::Texture::make_shared_from_file(const char* _path)
{
	if (!_path)
		throw Error("Texture", "File path is null");

	int width, height, channels;
	PixelsPtr pixels(stbi_load(_path, &width, &height, &channels, 0), stbi_image_free);
	if (!pixels)
		throw Error("Texture", "Loading from file failed");

	unsigned int format;
	if (!calc_format(channels, format))
		throw Error("Texture", "Undefined format");

	return std::make_shared<Texture>(GL_RGBA8, width, height, format, GL_UNSIGNED_BYTE, pixels.get());
}

std::shared_ptr<itd::graphics::Texture> itd::graphics::Texture::make_shared_from_memory(unsigned char* _buffer, int _buffer_size)
{
	if (!_buffer)
		throw Error("Texture", "Data buffer is empty");

	if (!_buffer_size)
		throw Error("Texture", "Data buffer size is empty");

	int width, height, channels;
	PixelsPtr pixels(stbi_load_from_memory(_buffer, _buffer_size, &width, &height, &channels, 0), stbi_image_free);
	if (!pixels)
		throw Error("Texture", "Loading from memory failed");

	unsigned int format;
	if (!calc_format(channels, format))
		throw Error("Texture", "Undefined format");

	return std::make_shared<Texture>(GL_RGBA8, width, height, format, GL_UNSIGNED_BYTE, pixels.get());
}

void itd::graphics::Texture::bind(unsigned int _active_index)
{
	glActiveTexture(GL_TEXTURE0 + _active_index);
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void itd::graphics::Texture::set_smooth(bool _smooth)
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _smooth ? GL_LINEAR : GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void itd::graphics::Texture::set_repeat(bool _repeat)
{
	glBindTexture(GL_TEXTURE_2D, m_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
}

glm::vec2 itd::graphics::Texture::size() const
{
	return m_size;
}

unsigned int itd::graphics::Texture::native() const
{
	return m_id;
}
