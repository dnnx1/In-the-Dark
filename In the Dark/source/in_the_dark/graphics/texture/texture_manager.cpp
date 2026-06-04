#include "in_the_dark/engine_api.h"
#include "in_the_dark/graphics/texture/texture_manager.h"

itd::graphics::TextureManager::TextureManager()
{
	EngineAPI::instance().textures = this;
}

itd::graphics::TextureManager::~TextureManager()
{
	if (EngineAPI::instance().textures == this)
		EngineAPI::instance().textures = nullptr;
}

std::unique_ptr<itd::graphics::TextureManager> itd::graphics::TextureManager::make_unique()
{
	return std::make_unique<TextureManager>();
}

void itd::graphics::TextureManager::add(std::string _name, std::shared_ptr<TextureAPI> _texture)
{
	try { m_container.add(_name, _texture); }
	catch (const std::exception& _e) { throw Error("Texture " + _name, _e.what()); }
}

std::shared_ptr<itd::graphics::TextureAPI> itd::graphics::TextureManager::get(std::string _name)
{
	try { return m_container.get(_name); }
	catch (const std::exception& _e) { throw Error("Texture " + _name, _e.what()); }
}
