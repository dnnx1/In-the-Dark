#include "in_the_dark/engine_api.h"
#include "in_the_dark/graphics/shader/shader_manager.h"

itd::graphics::ShaderManager::ShaderManager()
{
	EngineAPI::instance().shaders = this;
}

itd::graphics::ShaderManager::~ShaderManager()
{
	if (EngineAPI::instance().shaders == this)
		EngineAPI::instance().shaders = nullptr;
}

std::unique_ptr<itd::graphics::ShaderManager> itd::graphics::ShaderManager::make_unique()
{
	return std::make_unique<ShaderManager>();
}

void itd::graphics::ShaderManager::add(std::string _name, std::shared_ptr<ShaderAPI> _shader)
{
	try { m_container.add(_name, _shader); }
	catch (const std::exception& _e) { throw Error("Shader " + _name, _e.what()); }
}

std::shared_ptr<itd::graphics::ShaderAPI> itd::graphics::ShaderManager::get(std::string _name)
{
	try { return m_container.get(_name); }
	catch (const std::exception& _e) { throw Error("Shader " + _name, _e.what()); }
}
