#pragma once
#include "external/json/json.hpp"

namespace itd::world
{
	using json = nlohmann::json;

	class Object
	{
	public:
		Object() : m_unique_id(NEXT_ID++) {}
		virtual ~Object() = default;

	public:
		virtual json serialize() const = 0;
		uint32_t unique_id() const { return m_unique_id; }

	private:
		static inline uint32_t NEXT_ID = 0;
		uint32_t m_unique_id;
	};
}