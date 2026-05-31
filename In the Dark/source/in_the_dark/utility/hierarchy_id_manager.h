#pragma once
#include <cstdint>

namespace itd::utility
{
	template <typename Base>
	class HierarchyIDManager
	{
	public:
		template <typename Derived> static uint32_t get()
		{
			static uint32_t id = next_id();
			return id;
		}
	private:
		static uint32_t next_id()
		{
			static uint32_t counter = 0;
			return counter++;
		}
	};
}