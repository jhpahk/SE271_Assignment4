#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Commons.h"

#include <vector>
#include <random>

namespace snake_arena {
	class Unit;
	class Snake;
	class Fruit;

	class Player;
	class Canvas;

	enum class GameResult { Player1_Win, Player2_Win, GameDraw };

	// Environment class manages the entire game
	class Environment final {
	public:
		/**
		*   \brief Constructor
		*   \param map_size: the dimension size of a square-sized map
		*   \param n_fruits: the number of fruits created in the map
		*   \param l_fruits: the default length of snakes
		*   \param seed: The same seed creates the same order of fruits.
		*	If zero, we randomize it.
		**/
		Environment(
			int map_size, int n_fruits, int l_snake, int max_turns, int seed=0);

        // Destructor
		~Environment();

		/**
		*   \brief Set Player
		*   \param player1: the first player playing turns
		*   \param player2: the second player playing turns
		**/
		void setPlayers(Player* player1, Player* player2);

		/**
		*   \brief Play games for one n_round
		*   \param canvas: when given, draw the map on the console screen
		*   \return the game results
		**/
		GameResult play(Canvas* canvas = nullptr);

		/**
		*   \brief Get the number of turns played 
		*   \return the number of turns
		**/
		int getTurns() const { return turn;  }

	private:
		int map_size; 
		int n_fruits; 
		int l_snakes;
		int max_turns;
		int turn = -1;

		std::vector<Player*> players;
		std::vector<Unit*> all_units;
		std::vector<Fruit*> fruits;
		std::vector<Snake*> snakes;
		std::mt19937 random_gen;

	private:
		void initialize(int);
		Fruit* make_new_fruit();
		Pos _make_new_fruits(
			const std::vector<Pos>& all_positions, int fruit_loc);

		void paint(Canvas* canvas, int turn);
	};
}
