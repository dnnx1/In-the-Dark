#pragma once
#include <vector>
#include <algorithm>
#include "in_the_dark/utility/hierarchy_id_manager.h"

namespace itd::game_object
{
	class ISnapshotStorage;
	using SnapshotStorageTypeID = utility::HierarchyIDManager<ISnapshotStorage>;

	class ISnapshotStorage
	{
	public:
		virtual ~ISnapshotStorage() = default;

	public:
		virtual uint32_t type_id() const = 0;
	};

	template <typename Snapshot>
	class SnapshotStorage : public ISnapshotStorage
	{
	public:
		SnapshotStorage() = default;
		~SnapshotStorage() = default;

		SnapshotStorage(const SnapshotStorage&) = delete;
		SnapshotStorage(SnapshotStorage&&) = default;

		SnapshotStorage& operator=(const SnapshotStorage&) = delete;
		SnapshotStorage& operator=(SnapshotStorage&&) = default;

	public:
		uint32_t type_id() const override { return SnapshotStorageTypeID::get<Snapshot>(); }

		void push_back(const Snapshot& _snapshot) { m_snapshots.push_back(_snapshot); }
		void push_back(Snapshot&& _snapshot) { m_snapshots.push_back(std::move(_snapshot)); }

		const std::vector<Snapshot>& snapshots() const { return m_snapshots; }
		typename std::vector<Snapshot>::const_iterator begin() const { return m_snapshots.begin(); }
		typename std::vector<Snapshot>::const_iterator end() const { return m_snapshots.end(); }

	private:
		std::vector<Snapshot> m_snapshots;
	};
}