#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include <queue>
#include "engine/error.h"
#include "engine/scene/scene_manager/scene_manager_api.h"
#include "engine/scene/scene.h"

namespace itd::scene
{
	class SceneManager : public SceneManagerAPI
	{
	private:
		using ScenePtr = std::shared_ptr<IScene>;

		struct PushScene { unsigned int id; };
		struct PopScene {};
		struct ClearScenes {};
		using PendingChanges = std::variant<std::monostate, PushScene, PopScene, ClearScenes>;

	public:
		SceneManager();
		~SceneManager();

		SceneManager(const SceneManager&) = delete;
		SceneManager(SceneManager&&) = delete;

		SceneManager& operator=(const SceneManager&) = delete;
		SceneManager& operator=(SceneManager&&) = delete;

	public:
		static std::unique_ptr<SceneManager> make_unique();

	public:
		template <typename Type, typename ... Args> void create_scene(Args&& ..._args)
		{
			ScenePtr scene(new Type(std::forward<Args>(_args)...), [](IScene* _raw)
				{
					_raw->destroy_callback();
					delete _raw;
				});

			unsigned int type_id = scene->type_id();
			auto [it, inserted] = m_list.try_emplace(type_id, std::move(scene));
			if (!inserted)
				throw Error("SceneManager", std::to_string(type_id) + " scene already exists");

			it->second->create_callback();
		}

	public:
		void push_scene(unsigned int _id) override;
		void pop_scene() override;
		void clear_scenes() override;

		void destroy_scenes();
		void apply_pending_changes();

		void handle_messages(const core::Message& _message);
		void pre_update(float _dt);
		void fixed_update(float _fixed_dt);
		void post_update(float _dt);
		void prepare_render(float _alpha);
		void render();

	private:
		std::unordered_map<unsigned int, ScenePtr> m_list;
		std::vector<ScenePtr> m_stack;

		std::queue<PendingChanges> m_pending_changes;
		std::unordered_set<unsigned int> m_start_callback_used_list;
	};
}