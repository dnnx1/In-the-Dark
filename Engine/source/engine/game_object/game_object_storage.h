#pragma once
#include <vector>
#include <algorithm>
#include "engine/utility/hierarchy_id_manager.h"

namespace itd::game_object
{
	class IGameObjectStorage;
	using GameObjectStorageTypeID = utility::HierarchyIDManager<IGameObjectStorage>;

	class IGameObjectStorage
	{
	public:
		virtual ~IGameObjectStorage() = default;

	public:
		virtual uint32_t type_id() const = 0;
	};

	template <typename GameObject>
	class GameObjectStorage : public IGameObjectStorage
	{
	public:
		template <typename ...Args> void emplace(Args&& ..._args)
		{
			m_objects.emplace_back(std::forward<Args>(_args)...);
		}

		template <typename Predicate> void remove_if(Predicate&& _predicate)
		{
			std::erase_if(m_objects, std::forward<Predicate>(_predicate));
		}

	public:
		uint32_t type_id() const override { return GameObjectStorageTypeID::get<GameObject>(); }

		const std::vector<GameObject>& objects() const { return m_objects; }
		typename std::vector<GameObject>::const_iterator begin() const { return m_objects.begin(); }
		typename std::vector<GameObject>::const_iterator end() const { return m_objects.end(); }

	private:
		std::vector<GameObject> m_objects;
	};
}