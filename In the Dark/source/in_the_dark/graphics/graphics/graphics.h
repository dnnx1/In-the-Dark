#pragma once
#include <memory>
#include "in_the_dark/graphics/graphics/graphics_api.h"

namespace itd::graphics
{
	class Graphics : public GraphicsAPI
	{
	public:
		Graphics();
		~Graphics();

		Graphics(const Graphics&) = delete;
		Graphics(Graphics&&) = delete;

		Graphics& operator=(const Graphics&) = delete;
		Graphics& operator=(Graphics&&) = delete;

	public:
		static std::unique_ptr<Graphics> make_unique();

	public:
		void set_render_state(const RenderState& _state) override;
		void set_viewport(int _x, int _y, int _width, int _height) override;
		void clear_color_attachment(int _index, const float* _color) override;
		void clear_color_attachment_uint(int _index, const unsigned int* _color) override;
		void clear_depth_attachment(float _depth) override;

	private:
		RenderState m_state;
	};
}