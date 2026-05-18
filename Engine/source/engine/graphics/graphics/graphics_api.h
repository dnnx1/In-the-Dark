#pragma once
#include <cstdint>
#include "engine/utility/enum.h"

namespace itd::graphics
{
	class GraphicsAPI
	{
	public:
		enum class BlendFactor : uint8_t
		{
			Zero,
			One,

			SrcColor,
			OneMinusSrcColor,

			DstColor,
			OneMinusDstColor,

			SrcAlpha,
			OneMinusSrcAlpha,

			DstAlpha,
			OneMinusDstAlpha,
		};

		enum class DepthFunc : uint8_t
		{
			Always,
			Never,
			Less,
			Equal,
			LessEqual,
			Greater,
			GreaterEqual,
			NotEqual,
		};

		struct BlendState
		{
			bool enable{ false };
			BlendFactor src{ BlendFactor::SrcAlpha };
			BlendFactor dst{ BlendFactor::OneMinusSrcAlpha };
		};

		struct DepthState
		{
			bool test_enable{ false };
			bool write_enable{ false };
			DepthFunc func{ DepthFunc::LessEqual };
		};

		struct RenderState
		{
			BlendState blend;
			DepthState depth;
		};

	public:
		virtual ~GraphicsAPI() = default;

	public:
		virtual void set_render_state(const RenderState& _state) = 0;
		virtual void set_viewport(int _x, int _y, int _width, int _height) = 0;
		virtual void clear_color_attachment(int _index, const float* _color) = 0;
		virtual void clear_color_attachment_uint(int _index, const unsigned int* _color) = 0;
		virtual void clear_depth_attachment(float _depth) = 0;
	};
}