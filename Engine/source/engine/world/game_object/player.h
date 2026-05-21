#pragma once
#include "engine/world/object.h"

namespace itd::world
{
	class Player : public Object
	{
	public:
		json serialize() const override { return {}; };
	};
}