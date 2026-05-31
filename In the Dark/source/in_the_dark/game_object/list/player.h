#pragma once

namespace itd::game_object
{
	class Player
	{
	public:
		struct Snapshot
		{

		};

	public:
		Player(const Snapshot& _snapshot);
		Player() = default;
		~Player() = default;

		Player(const Player&) = default;
		Player(Player&&) = default;

		Player& operator=(const Player&) = default;
		Player& operator= (Player&&) = default;

	public:
		Snapshot make_snapshot() const;
	};
}