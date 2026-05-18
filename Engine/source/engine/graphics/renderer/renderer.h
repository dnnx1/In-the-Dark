#pragma once
#include <memory>
#include "engine/graphics/renderer/renderer_api.h"

namespace itd::graphics
{
	class Renderer : public RendererAPI
	{
	public:
		Renderer();
		~Renderer();

		Renderer(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;

		Renderer& operator=(const Renderer&) = delete;
		Renderer& operator=(Renderer&&) = delete;

	public:
		static std::unique_ptr<Renderer> make_unique();
	};
}