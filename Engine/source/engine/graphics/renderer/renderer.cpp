#include "engine/core/engine_api.h"
#include "engine/graphics/renderer/renderer.h"

itd::graphics::Renderer::Renderer()
{
	core::EngineAPI::instance().renderer = this;
}

itd::graphics::Renderer::~Renderer()
{
	if (core::EngineAPI::instance().renderer == this)
		core::EngineAPI::instance().renderer = nullptr;
}

std::unique_ptr<itd::graphics::Renderer> itd::graphics::Renderer::make_unique()
{
	return std::make_unique<Renderer>();
}
