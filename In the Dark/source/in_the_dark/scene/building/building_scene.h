#pragma once
#include <atomic>
#include "in_the_dark/scene/scene.h"

namespace itd::scene
{
	class BuildingScene : public Scene<BuildingScene>
	{
	private:
		enum class State : uint8_t
		{
			BuildResourcesStarted,
			BuildResourcesInProgress,
			BuildScenesStarted,
			BuildScenesInProgress,

			BuildCompleted
		};

	public:
		BuildingScene() = default;
		~BuildingScene() = default;

		BuildingScene(const BuildingScene&) = delete;
		BuildingScene(BuildingScene&&) = delete;

		BuildingScene& operator=(const BuildingScene&) = delete;
		BuildingScene& operator=(BuildingScene&&) = delete;

	public:
		void create_callback() override;

		void pre_update(float _dt) override;

	private:
		std::atomic<State> m_state{ State::BuildResourcesStarted };
	};
}