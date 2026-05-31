#include "in_the_dark/engine_api.h"
#include "in_the_dark/scene/scene_manager/scene_manager.h"

itd::scene::SceneManager::SceneManager()
{
	EngineAPI::instance().scenes = this;
}

itd::scene::SceneManager::~SceneManager()
{
	if (EngineAPI::instance().scenes == this)
		EngineAPI::instance().scenes = nullptr;
}

std::unique_ptr<itd::scene::SceneManager> itd::scene::SceneManager::make_unique()
{
	return std::make_unique<SceneManager>();
}

void itd::scene::SceneManager::push_scene(uint32_t _id)
{
	EngineAPI::instance().main_thread_worker->push([this, type_id = _id]()
		{
			auto it = m_list.find(type_id);
			if (it == m_list.end())
				throw Error("SceneManager", "Undefined scene " + std::to_string(type_id));

			bool already_in_stack = std::find_if(m_stack.begin(), m_stack.end(), [type_id](const ScenePtr& _scene)
				{
					return _scene->type_id() == type_id;
				}) != m_stack.end();

			if (already_in_stack)
			{
				std::string err("Scene "); err += std::to_string(type_id); err += " already in stack";
				throw Error("SceneManager", err);
			}

			if (m_start_callback_used_list.find(type_id) == m_start_callback_used_list.end())
			{
				m_start_callback_used_list.insert(type_id);
				it->second->start_callback();
			}
			it->second->push_callback();

			m_stack.push_back(it->second);
		});
}

void itd::scene::SceneManager::pop_scene()
{
	EngineAPI::instance().main_thread_worker->push([this]()
		{
			if (m_stack.empty())
				throw Error("SceneManager", "Scene stack is empty");

			m_stack.back()->pop_callback();
			m_stack.pop_back();
		});
}

void itd::scene::SceneManager::clear_scenes()
{
	EngineAPI::instance().main_thread_worker->push([this]()
		{
			for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++)
				(*it)->pop_callback();

			m_stack.clear();
		});
}

void itd::scene::SceneManager::destroy_scenes()
{
	m_stack.clear();
	m_list.clear();
}

void itd::scene::SceneManager::handle_messages(const core::Message& _message)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++)
		(*it)->handle_messages(_message);
}

void itd::scene::SceneManager::pre_update(float _dt)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++)
		(*it)->pre_update(_dt);
}

void itd::scene::SceneManager::fixed_update(float _fixed_dt)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++)
		(*it)->fixed_update(_fixed_dt);
}

void itd::scene::SceneManager::post_update(float _dt)
{
	for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++)
		(*it)->post_update(_dt);
}

void itd::scene::SceneManager::render(float _alpha)
{
	for (auto& scene : m_stack)
		scene->render(_alpha);
}
