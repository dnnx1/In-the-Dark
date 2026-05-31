#pragma once
#include <string>
#include "in_the_dark/core/message/message.h"
#include "in_the_dark/utility/hierarchy_id_manager.h"

namespace itd::scene
{
	class IScene;
	using SceneTypeID = utility::HierarchyIDManager<IScene>;

	class IScene
	{
	public:
		virtual ~IScene() = default;

	public:
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
	};

	template <typename Derived>
	class Scene : public IScene
	{
	public:
		uint32_t type_id() const override { return SceneTypeID::get<Derived>(); }
	};
}