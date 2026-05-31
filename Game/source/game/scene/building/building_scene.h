#pragma once
#include "engine/scene/scene.h"

namespace itd::scene
{
	class BuildingScene : public Scene<BuildingScene>
	{
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
	};
}