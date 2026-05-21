#pragma once
#include <string>
#include "engine/core/message/message.h"
#include "engine/utility/hierarchy_id_manager.h"
#include "engine/world/world.h"

namespace itd::scene
{
	class IScene;
	using SceneTypeID = utility::HierarchyIDManager<IScene>;

	class IScene
	{
	public:
		virtual ~IScene() = default;

	public:
		void apply_pending_changes() { m_world.apply_pending_changes(); }
		void move_world(world::World&& _world) { m_world = std::move(_world); }

		virtual uint32_t type_id() const = 0;

		virtual void create_callback() {}
		virtual void destroy_callback() {}
		virtual void start_callback() {}
		virtual void push_callback() {}
		virtual void pop_callback() {}

		virtual void handle_messages(const core::Message& _message) {}
		virtual void pre_update(float _dt) {}
		virtual void fixed_update(float _fixed_dt) {}
		virtual void post_update(float _dt) {}
		virtual void prepare_render(float _alpha) {}
		virtual void render() {}

	protected:
		template <typename ObjectType> inline world::ObjectStorageAPI<ObjectType>& storage() { return m_world.storage<ObjectType>(); }

	private:
		world::World m_world;
	};

	template <typename Derived>
	class Scene : public IScene
	{
	public:
		virtual ~Scene() = default;

	public:
		uint32_t type_id() const override { return SceneTypeID::get<Derived>(); }

	private:
		using IScene::apply_pending_changes;
	};
}