#pragma once
#include <cmath>
#include "external/glm/vec2.hpp"

namespace itd::utility
{
	template <typename Type> inline Type lerp(Type _start, Type _end, float _amount)
	{
		return _start + (_end - _start) * _amount;
	}

	inline bool epsilon_equal(float _left, float _right, float _eps = 1e-6f)
	{
		return std::abs(_left - _right) <= _eps;
	}

	inline bool epsilon_less(float _left, float _right, float _eps = 1e-6f)
	{
		return _left < (_right - _eps);
	}

	inline bool epsilon_greater(float _left, float _right, float _eps = 1e-6f)
	{
		return _left > _right + _eps;
	}
}