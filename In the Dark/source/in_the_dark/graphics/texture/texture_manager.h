#pragma once
#include "in_the_dark/graphics/texture/texture_manager_api.h"
#include "in_the_dark/utility/resource_container.h"

namespace itd::graphics
{
	class TextureManager : public TextureManagerAPI
	{
	private:
		using Container = utility::ResourceContainer<std::string, TextureAPI>;

	public:
		TextureManager();
		~TextureManager();

		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;

		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(TextureManager&&) = delete;

	public:
		static std::unique_ptr<TextureManager> make_unique();

	public:
		void add(std::string _name, std::shared_ptr<TextureAPI> _texture) override;
		std::shared_ptr<TextureAPI> get(std::string _name) override;

	private:
		Container m_container;
	};
}