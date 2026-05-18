#include "engine/engine_api.h"
#include "engine/graphics/renderer/renderer.h"

itd::graphics::Renderer::Renderer()
{
	EngineAPI::instance().renderer = this;
}

itd::graphics::Renderer::~Renderer()
{
	if (EngineAPI::instance().renderer == this)
		EngineAPI::instance().renderer = nullptr;
}

std::unique_ptr<itd::graphics::Renderer> itd::graphics::Renderer::make_unique()
{
	return std::make_unique<Renderer>();
}
