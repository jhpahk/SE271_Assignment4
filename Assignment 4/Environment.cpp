////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Environment.h"

#include "Fruit.h"
#include "Snake.h"
#include "Player.h"

#include "Canvas.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cassert>

namespace snake_arena {
	Environment::Environment(
		int map_size, int n_fruits, int l_snakes, int max_turns, int seed) :
		map_size(map_size), n_fruits(n_fruits),
		l_snakes(l_snakes), max_turns(max_turns) {
		initialize(seed);
	}

	Environment::~Environment() {
		for (auto& unit : all_units) {
			delete unit;
		}
	}

	void Environment::initialize(int seed) {
		if (seed == 0) {
			std::random_device rd;
			random_gen.seed(rd());
		}
		else {
			random_gen.seed(seed);
		}

		// Create fruits
		while (fruits.size() != n_fruits) {
			fruits.push_back(make_new_fruit());
		}

		// Create snakes
		// Note: This class is designed to mostly support many snakes for more fun
		// Flexibility and extendability are usually good!
		// But, we here use two snakes only in this class.
		Pos snake1_pos(map_size / 4, map_size / 4);
		Direction snake1_direction = DrtS();
		Pos snake2_pos(map_size - map_size / 4, map_size - map_size / 4);
		Direction snake2_direction = DrtN();

		std::uniform_real_distribution<float> coin(0, 1);
		if (coin(random_gen) >= 0.5) {
			std::swap(snake1_pos, snake2_pos);
			std::swap(snake1_direction, snake2_direction);
		}

		Snake* snake1 = new Snake(snake1_pos, snake1_direction, l_snakes);
		snakes.push_back(snake1);
		all_units.push_back(snake1); // Memory will be freed using this

		Snake* snake2 = new Snake(snake2_pos, snake2_direction, l_snakes);
		snakes.push_back(snake2);
		all_units.push_back(snake2); // Memory will be freed using this
	}

	void Environment::setPlayers(Player* player1, Player* player2) {
		this->players.push_back(player1);
		this->players.push_back(player2);
	}

	GameResult Environment::play(Canvas* canvas) {
		if (players.size() != 2) {
			std::cout << "Two players should be set first!" << std::endl;
			return GameResult::GameDraw;
		}

		// Draw canvas
		if (canvas != nullptr) {
			paint(canvas, 0);
		}

		// Play turns
		for (turn = 0; turn < max_turns; ++turn) {
			if (turn == 285)
				turn = 285;

			// Move snakes and check hits
			for (int player_idx = 0; player_idx < 2; ++player_idx) {
				auto snake = snakes[player_idx];

				// 1. Select direction by the player and get the next head if moved
				if (player_idx == 0) {
					snake->setDirection(
						players[0]->selectDirection(
							turn, snakes[0], snakes[1], fruits));
				}
				else {
					snake->setDirection(
						players[1]->selectDirection(
							turn, snakes[1], snakes[0], fruits));
				}
				Pos head = snake->getNextHead();

				// 2. Check crashes
				for (auto& _snake : snakes) { // Check crashes with the snake body
					if (_snake->hit(head)) {
						snake->setCrashed();
						break;
					}
				}

				if (head.x < 0 || head.x >= map_size ||
					head.y < 0 || head.y >= map_size) { // Check crashes with wall
					snake->setCrashed();
				}

				if (snake->isCrashed())
					break;

				// 3. Now, we can move and check if it gets a fruit
				snake->move();
				Fruit* taken = nullptr;
				for (auto& fruit : fruits) {
					if (fruit->hit(head)) {
						snake->grow();
						taken = fruit;
					}
				}

				if (taken != nullptr) {
					// Delete the taken fruit and make a new fruit
					fruits.erase(std::remove(fruits.begin(), fruits.end(), taken), fruits.end());
					all_units.erase(std::remove(all_units.begin(), all_units.end(), taken), all_units.end());
					delete taken;
					fruits.push_back(make_new_fruit());
				}
			}

			// Update canvas
			if (canvas != nullptr) {
				paint(canvas, turn + 1);
			}

			// Check game results
			if (snakes[0]->isCrashed()) {
				return GameResult::Player2_Win;
			}

			if (snakes[1]->isCrashed()) {
				return GameResult::Player1_Win;
			}
		}


		// Draw. return results using lengths
		if (snakes[0]->getLength() == snakes[1]->getLength()) {
			return GameResult::GameDraw;
		} else if (snakes[0]->getLength() > snakes[1]->getLength()) {
			return GameResult::Player1_Win;
		} 

		return GameResult::Player2_Win; // otherwise Player 2 wins by the length!
	}

	Pos Environment::_make_new_fruits(
		const std::vector<Pos>& all_positions, int fruit_loc) {
		int curloc = 0;
		for (int y = 0; y < map_size; ++y) {
			for (int x = 0; x < map_size; ++x) {
				if (exists(all_positions, Pos(x, y)))
					continue;
				if (curloc == fruit_loc)
					return Pos(x, y);
				++curloc;
			}
		}

		std::cout << fruit_loc << std::endl;
		std::cout.flush();
		assert(false); // Unreachable as long as the map is not completely full
		return Pos(0, 0);
	}

	Fruit* Environment::make_new_fruit() {
		std::vector<Pos> all_positions;

		// Collect all positions
		for (auto& fruit : fruits) {
			appendVector(all_positions, fruit->getPositions());
		}
		for (auto& snake : snakes) {
			appendVector(all_positions, snake->getPositions());
		}

		// Make new fruit
		std::uniform_int_distribution<int> posmaker(
			0, (map_size * map_size) - all_positions.size() - 2);
		Pos fruit_pos = _make_new_fruits(all_positions, posmaker(random_gen));

		Fruit* fruit = new Fruit(fruit_pos);
		all_units.push_back(fruit); // Adding it to clear memory later

		return fruit;
	}


	void Environment::paint(Canvas* canvas, int turn) {
		// Create the map buffer to paint
		const int extra_space = 10;
		char** map = new char*[map_size];
		for (int i = 0; i < map_size; ++i) {
			map[i] = new char[map_size + extra_space];
			memset(map[i], ' ', map_size + extra_space - 1);
			map[i][0] = '|';
			sprintf_s(&map[i][map_size+1], extra_space - 1, "|%2d", i);
		}

		// Paint fruits
		for (auto& fruit : fruits) {
			map[fruit->y][fruit->x + 1] = '$';
		}

		// Paint heads: Change the following characters to support multiple snakes
		char snake_head_chr[] = {'O', '@'};
		char snake_body_chr[] = {'U', '%'};
		assert(sizeof(snake_head_chr) == snakes.size()); 
		assert(sizeof(snake_body_chr) == snakes.size());
		for (size_t i = 0; i < snakes.size(); ++i) {
			auto body = snakes[i]->getPositions();
			for (auto pos : body) {
				if (pos == body.front()) {
					map[pos.y][pos.x + 1] = snake_head_chr[i];
				} else {
					map[pos.y][pos.x + 1] = snake_body_chr[i];
				}
			}
		}

		// paint each line from top
		canvas->addLine(std::string(map_size + 2, '-').c_str());
		for (int i = 0; i < map_size; ++i) {
			canvas->addLine(map[i]);
		}
		canvas->addLine(std::string(map_size + 2, '-').c_str());

		// Paint the x axis
		char* buffer = map[0]; // memory reuse
		for (int i = 0; i < map_size; ++i) {
			buffer[i + 1] = (i % 10) + '0';
		}
		buffer[0] = ' ';
		buffer[map_size + 1] = '\0';
		canvas->addLine(buffer);

		// Paint game information
		std::stringstream ssbuffer;
		ssbuffer << "Turn: " << turn;
		ssbuffer << " | P1: " << snakes[0]->getLength();
		ssbuffer << " , P2: " << snakes[1]->getLength();
		canvas->addLine(ssbuffer.str().c_str());
		ssbuffer.str(""); ssbuffer.clear();
		ssbuffer << "P1: " << players[0]->getName();
		canvas->addLine(ssbuffer.str().c_str());
		ssbuffer.str(""); ssbuffer.clear();
		ssbuffer << "P2: " << players[1]->getName();
		canvas->addLine(ssbuffer.str().c_str());

		// Draw !
		canvas->draw();

		// Delete the buffer 
		for (int i = 0; i < map_size; ++i) {
			delete[] map[i];
		}
		delete[] map;
	}
}
