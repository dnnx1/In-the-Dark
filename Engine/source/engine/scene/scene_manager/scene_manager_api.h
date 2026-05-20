#pragma once

namespace itd::scene
{
	class SceneManagerAPI
	{
	public:
		virtual ~SceneManagerAPI() = default;

	public:
		virtual void push_scene(unsigned int _id) = 0;
		virtual void pop_scene() = 0;
		virtual void clear_scenes() = 0;
	};
}