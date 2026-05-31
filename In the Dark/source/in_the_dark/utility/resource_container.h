#pragma once
#include <unordered_map>
#include <memory>
#include "in_the_dark/error.h"

namespace itd::utility
{
	template <typename Key, typename Resource>
	class ResourceContainer
	{
	public:
		void add(const Key& _key, std::shared_ptr<Resource> _resource)
		{
			if (!_resource)
				throw Error("Resource", "Resource is empty");

			auto [it, inserted] = m_resources.try_emplace(_key, std::move(_resource));
			if (!inserted)
				throw Error("Resource", "Resource already exists");
		}

		std::shared_ptr<Resource> get(const Key& _key)
		{
			auto it = m_resources.find(_key);
			if (it == m_resources.end())
				throw Error("Resource", "Resource does not exists");

			return it->second;
		}

	private:
		std::unordered_map<Key, std::shared_ptr<Resource>> m_resources;
	};
}