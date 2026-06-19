#include "in_the_dark/engine_api.h"
#include "in_the_dark/scene/building/building_scene.h"

#include "in_the_dark/ecs/core/world.h"

struct Transform
{
	glm::vec2 pos;
};

struct Gravity
{
	float value;
};

struct Trigger
{
	bool enabled;
};

void itd::scene::BuildingScene::create_callback()
{
	ecs::World world;

	world.create_entity(Transform{ {1.0f, 2.0f} }, Gravity{ 3.0f });

	world.create_entity(Transform{ {10.0f, 20.0f} }, Trigger{ false });

	world.create_entity(Transform{ {100.0f, 200.0f} }, Gravity{ 300.0f });

	world.create_entity(Trigger{ true }, Transform{ {1000.0f, 20000.0f} }, Gravity{ 1000.0f });

	Transform t1{ {50.0f, 60.0f} };
	Transform t2{ {590.0f, 690.0f} };

	world.create_entity(t1);
	world.create_entity(t2);

	world.create_entity(Gravity{ 5.0f }, t1);

	world.for_each<Transform>([](Transform& _transform)
		{
			static int counter = 0;
			printf("%d) %.0fx%.0f\n", counter++, _transform.pos.x, _transform.pos.y);
		});
}

void itd::scene::BuildingScene::pre_update(float _dt)
{
	switch (m_state.load())
	{
	case State::BuildResourcesStarted:
	{

	} break;

	case State::BuildResourcesInProgress:
	{

	} break;

	case State::BuildScenesStarted:
	{

	} break;

	case State::BuildScenesInProgress:
	{

	} break;

	case State::BuildCompleted:
	{
		EngineAPI::instance().scenes->clear_scenes();

		EngineAPI::instance().message_bus->send(core::BuildCompletedMessage{});
	} break;

	default:
		break;
	}
}