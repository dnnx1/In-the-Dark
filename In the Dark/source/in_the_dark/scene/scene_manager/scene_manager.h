#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory>
#include "in_the_dark/error.h"
#include "in_the_dark/scene/scene_manager/scene_manager_api.h"
#include "in_the_dark/scene/scene.h"

namespace itd::scene
{
	class SceneManager : public SceneManagerAPI
	{
	private:
		using ScenePtr = std::shared_ptr<IScene>;

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

			auto type_id = scene->type_id();
			auto [it, inserted] = m_list.try_emplace(type_id, std::move(scene));
			if (!inserted)
				throw Error("SceneManager", std::to_string(type_id) + " scene already exists");

			it->second->create_callback();
		}

	public:
		void push_scene(uint32_t _id) override;
		void pop_scene() override;
		void clear_scenes() override;

		void destroy_scenes();

		void handle_messages(const core::Message& _message);
		void pre_update(float _dt);
		void fixed_update(float _fixed_dt);
		void post_update(float _dt);
		void render(float _alpha);

	private:
		std::unordered_map<uint32_t, ScenePtr> m_list;
		std::vector<ScenePtr> m_stack;

		std::unordered_set<uint32_t> m_start_callback_used_list;
	};
}