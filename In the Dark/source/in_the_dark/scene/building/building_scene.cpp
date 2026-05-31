#include "in_the_dark/engine_api.h"
#include "in_the_dark/scene/building/building_scene.h"

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