#pragma once
#include "in_the_dark/scene/scene.h"

namespace itd::scene
{
	class GameScene : public Scene<GameScene>
	{
	public:
		GameScene() = default;
		~GameScene() = default;

		GameScene(const GameScene&) = delete;
		GameScene(GameScene&&) = delete;

		GameScene& operator=(const GameScene&) = delete;
		GameScene& operator=(GameScene&&) = delete;

	};
}