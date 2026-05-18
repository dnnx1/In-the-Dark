#include "external/GL/glew.h"
#include "engine/engine_api.h"
#include "engine/error.h"	
#include "engine/graphics/graphics/graphics.h"

static unsigned int to_native_blend_factor(itd::graphics::Graphics::BlendFactor _blend_factor)
{
	using BlendFactor = itd::graphics::Graphics::BlendFactor;
	switch (_blend_factor)
	{
	case BlendFactor::Zero:				return GL_ZERO;
	case BlendFactor::One:				return GL_ONE;
	case BlendFactor::SrcColor:			return GL_SRC_COLOR;
	case BlendFactor::OneMinusSrcColor:	return GL_ONE_MINUS_SRC_COLOR;
	case BlendFactor::DstColor:			return GL_DST_COLOR;
	case BlendFactor::OneMinusDstColor:	return GL_ONE_MINUS_DST_COLOR;
	case BlendFactor::SrcAlpha:			return GL_SRC_ALPHA;
	case BlendFactor::OneMinusSrcAlpha:	return GL_ONE_MINUS_SRC_ALPHA;
	case BlendFactor::DstAlpha:			return GL_DST_ALPHA;
	case BlendFactor::OneMinusDstAlpha:	return GL_ONE_MINUS_DST_ALPHA;

	default: throw itd::Error("Graphics", "Invalid blend factor");
	}
}

static unsigned int to_native_depth_func(itd::graphics::Graphics::DepthFunc _depth_func)
{
	using DepthFunc = itd::graphics::Graphics::DepthFunc;
	switch (_depth_func)
	{
	case DepthFunc::Always:			return GL_ALWAYS;
	case DepthFunc::Never:			return GL_NEVER;
	case DepthFunc::Less:			return GL_LESS;
	case DepthFunc::Equal:			return GL_EQUAL;
	case DepthFunc::LessEqual:		return GL_LEQUAL;
	case DepthFunc::Greater:		return GL_GREATER;
	case DepthFunc::GreaterEqual:	return GL_GEQUAL;
	case DepthFunc::NotEqual:		return GL_NOTEQUAL;

	default: throw itd::Error("Graphics", "Invalid depth func");
	}
}

itd::graphics::Graphics::Graphics()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		throw Error("Graphics", "GLEW initialization failed");

	m_state.blend.enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	glBlendFunc(to_native_blend_factor(m_state.blend.src), to_native_blend_factor(m_state.blend.dst));

	m_state.depth.test_enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	glDepthMask(m_state.depth.write_enable ? GL_TRUE : GL_FALSE);
	glDepthFunc(to_native_depth_func(m_state.depth.func));

	EngineAPI::instance().graphics = this;
}

itd::graphics::Graphics::~Graphics()
{
	if (EngineAPI::instance().graphics == this)
		EngineAPI::instance().graphics = nullptr;
}

std::unique_ptr<itd::graphics::Graphics> itd::graphics::Graphics::make_unique()
{
	return std::make_unique<Graphics>();
}

void itd::graphics::Graphics::set_render_state(const RenderState& _state)
{
	if (m_state.blend.enable != _state.blend.enable)
	{
		m_state.blend.enable = _state.blend.enable;
		m_state.blend.enable ? glEnable(GL_BLEND) : glDisable(GL_BLEND);
	}

	if (m_state.blend.src != _state.blend.src || m_state.blend.dst != _state.blend.dst)
	{
		m_state.blend.src = _state.blend.src;
		m_state.blend.dst = _state.blend.dst;
		glBlendFunc(to_native_blend_factor(m_state.blend.src), to_native_blend_factor(m_state.blend.dst));
	}

	if (m_state.depth.test_enable != _state.depth.test_enable)
	{
		m_state.depth.test_enable = _state.depth.test_enable;
		m_state.depth.test_enable ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
	}

	if (m_state.depth.write_enable != _state.depth.write_enable)
	{
		m_state.depth.write_enable = _state.depth.write_enable;
		glDepthMask(m_state.depth.write_enable ? GL_TRUE : GL_FALSE);
	}

	if (m_state.depth.func != _state.depth.func)
	{
		m_state.depth.func = _state.depth.func;
		glDepthFunc(to_native_depth_func(m_state.depth.func));
	}
}

void itd::graphics::Graphics::set_viewport(int _x, int _y, int _width, int _height)
{
	glViewport(_x, _y, _width, _height);
}

void itd::graphics::Graphics::clear_color_attachment(int _index, const float* _color)
{
	glClearBufferfv(GL_COLOR, _index, _color);
}

void itd::graphics::Graphics::clear_color_attachment_uint(int _index, const unsigned int* _color)
{
	glClearBufferuiv(GL_COLOR, _index, _color);
}

void itd::graphics::Graphics::clear_depth_attachment(float _depth)
{
	glClearBufferfv(GL_DEPTH, 0, &_depth);
}
