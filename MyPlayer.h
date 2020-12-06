#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "Player.h"
#include "Commons.h"

#include <string>

#define MyPlayer		Player201911067		// CHANGE THIS: Your StudentID 
#define PLAYER_NAME		"Best Driver"	// CHANGE THIS: Name your player

namespace snake_arena {
	class MyPlayer final : public Player {
	public:
		MyPlayer(int map_size);
		virtual ~MyPlayer() override;

		virtual std::string getName() const { return PLAYER_NAME; }
		virtual Direction selectDirection(
			int turn, Snake* player_snake, Snake* enemy_snake,
			std::vector<Fruit*> fruits);
	private:
		int mapsize;
		char ex_check_dir[15][15];
		int map_checked[15][15];
		bool map_can_go[15][15];
		int p_x;
		int p_y;
		int e_x;
		int e_y;

		bool can_go_outside(int map[15][15], int x, int y, bool wall[4]);
	};
}
