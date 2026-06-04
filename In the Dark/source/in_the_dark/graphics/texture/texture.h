#pragma once
#include <memory>
#include "in_the_dark/graphics/texture/texture_api.h"

namespace itd::graphics
{
	class Texture : public TextureAPI
	{
	public:
		enum class Format : uint8_t
		{
			R8,
			R16F,
			RGB8,
			RGB16F,
			RGBA8,
			RGBA16F,
		};

	private:
		using PixelsPtr = std::unique_ptr<unsigned char, void(*)(void*)>;

	public:
		Texture(int _iformat, int _width, int _height, unsigned int _format, unsigned int _type, unsigned char* _pixels);
		~Texture();

		Texture(const Texture&) = delete;
		Texture(Texture&&) = delete;

		Texture& operator=(const Texture&) = delete;
		Texture& operator=(Texture&&) = delete;

	public:
		static std::shared_ptr<Texture> make_shared_empty(Format _format, int _width, int _height);
		static std::shared_ptr<Texture> make_shared_from_file(const char* _path);
		static std::shared_ptr<Texture> make_shared_from_memory(unsigned char* _buffer, int _buffer_size);

	public:
		void bind(unsigned int _active_index = 0) override;
		void set_smooth(bool _smooth) override;
		void set_repeat(bool _repeat) override;
		glm::vec2 size() const override;
		unsigned int native() const override;

	private:
		unsigned int m_id{ 0 };
		glm::vec2 m_size{ 0.0f };
	};
}