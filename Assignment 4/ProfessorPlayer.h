#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
// This is an example implementation of the snake strategy.
// The compiled object file is provided.
////////////////////////////////////////////////////////////////////////////////

#include "Player.h"

namespace snake_arena {
	class Direction;

	class ProfFruitTaker : public Player {
	public:
		ProfFruitTaker(int);
		virtual ~ProfFruitTaker() override;

		virtual std::string getName() const { return "Prof. Fruit Taker"; }
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits);

	private:
		bool** unknown_variable1 = nullptr;
		Direction** unknown_variable2 = nullptr;
		bool** unknown_variable3 = nullptr;
		bool unknown_func(
			const Pos&, const Pos&, const Direction&, const std::vector<Pos>&);
	};

	class ProfNeverDie : public Player {
	public:
		ProfNeverDie(int);
		virtual ~ProfNeverDie() override;

		virtual std::string getName() const { return "Prof. NeverDie"; }
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits);

	private:
		bool** unknown_variable1 = nullptr;
		Direction** unknown_variable2 = nullptr;
		bool** unknown_variable3 = nullptr;
		bool unknown_func1(
			const Pos&, Pos&,
			const Direction&, const std::vector<Pos>&, bool);
		bool unknown_func2(
			const Pos&, Pos&, const Direction&, const std::vector<Pos>&);
		bool unknown_func3(
			const Pos&, const Pos&, const Direction&,
			const std::vector<Pos>&, Direction&);
	};
}

