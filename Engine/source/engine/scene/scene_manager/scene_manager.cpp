#include "engine/engine_api.h"
#include "engine/scene/scene_manager/scene_manager.h"

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

void itd::scene::SceneManager::push_scene(unsigned int _id)
{
	m_pending_changes.push(PushScene{ _id });
}

void itd::scene::SceneManager::pop_scene()
{
	m_pending_changes.push(PopScene{});
}

void itd::scene::SceneManager::clear_scenes()
{
	m_pending_changes.push(ClearScenes{});
}

void itd::scene::SceneManager::destroy_scenes()
{
	m_pending_changes = {};
	m_stack.clear();
	m_list.clear();
}

void itd::scene::SceneManager::apply_pending_changes()
{
	while (!m_pending_changes.empty())
	{
		if (auto* pending = std::get_if<PushScene>(&m_pending_changes.front()))
		{
			auto it = m_list.find(pending->id);
			if (it == m_list.end())
				throw Error("SceneManager", "Undefined scene " + std::to_string(pending->id));

			bool already_in_stack = std::find_if(m_stack.begin(), m_stack.end(), [id = pending->id](const ScenePtr& _scene)
				{
					return _scene->type_id() == id;
				}) != m_stack.end();

			if (already_in_stack)
			{
				std::string err("Scene "); err += std::to_string(pending->id); err += " already in stack";
				throw Error("SceneManager", err);
			}

			if (m_start_callback_used_list.find(pending->id) == m_start_callback_used_list.end())
			{
				m_start_callback_used_list.insert(pending->id);
				it->second->start_callback();
			}
			it->second->push_callback();

			m_stack.push_back(it->second);
		}
		else if (std::holds_alternative<PopScene>(m_pending_changes.front()))
		{
			if (m_stack.empty())
				throw Error("SceneManager", "Scene stack is empty");

			m_stack.back()->pop_callback();
			m_stack.pop_back();
		}
		else if (std::holds_alternative<ClearScenes>(m_pending_changes.front()))
		{
			for (auto it = m_stack.rbegin(); it != m_stack.rend(); it++)
				(*it)->pop_callback();

			m_stack.clear();
		}

		m_pending_changes.pop();
	}
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

void itd::scene::SceneManager::prepare_render(float _alpha)
{
	for (auto& scene : m_stack)
		scene->prepare_render(_alpha);
}

void itd::scene::SceneManager::render()
{
	for (auto& scene : m_stack)
		scene->render();
}
