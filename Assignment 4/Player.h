#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
// You will derive the Player class and implement your strategy
////////////////////////////////////////////////////////////////////////////////

#include "Commons.h"

#include <string>

namespace snake_arena {
	class Snake;
	class Fruit;

	// Player class who moves the snake !
	// You will derive this class to implement your strategy
	class Player {
	public:
		Player(int map_size) : map_size(map_size) {};
		virtual ~Player() {};
		virtual std::string getName() const = 0;
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits) = 0;
	protected:
		int map_size;
	};
}



