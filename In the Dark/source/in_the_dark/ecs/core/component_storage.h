#pragma once
#include <vector>
#include "in_the_dark/utility/hierarchy_id_manager.h"

namespace itd::ecs
{
	struct IComponentStorage;
	using ComponentStorageTypeID = utility::HierarchyIDManager<IComponentStorage>;

	struct IComponentStorage
	{
		virtual ~IComponentStorage() = default;
	};

	template <typename Component>
	struct ComponentStorage : public IComponentStorage
	{
		std::vector<Component> components;
	};
}