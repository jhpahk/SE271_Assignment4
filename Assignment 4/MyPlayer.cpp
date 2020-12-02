////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You WILL SUBMIT THIS FILE !!!
// Implement your strategy, whatever you want
// You can modify anything as long as it can be compiled with the provided code
// The current implementation simplely rotates the snake every turn
////////////////////////////////////////////////////////////////////////////////

#include "MyPlayer.h"

#include "Commons.h"
#include "Snake.h"
#include "Fruit.h"

namespace snake_arena {
	// Constructor
	MyPlayer::MyPlayer(int map_size) :
		Player(map_size) {
	}

	// Destructor
	MyPlayer::~MyPlayer() {

	}

	// Your function to primarily implement
	Direction MyPlayer::selectDirection(int turn, Snake* player_snake, Snake* enemy_snake, std::vector<Fruit*> fruits) {
		int player_len = player_snake->getLength();
		Pos player_head = player_snake->getPositions()[0];

		int enemy_len = enemy_snake->getLength();
		Pos enemy_head = enemy_snake->getPositions()[0];
		
		int fruit_num = fruits.size();

		Pos* fruits_pos = new Pos[fruit_num];
		int* fruit_distance = new int[fruit_num];

		for (int i = 0; i < fruit_num; i++) {
			fruits_pos[i] = (fruits[i])->getPositions()[0];
		}

		for (int i = 0; i < fruit_num; i++) {
			int plr_distance = (player_head.x - fruits_pos[i].x) * (player_head.x - fruits_pos[i].x) + (player_head.y - fruits_pos[i].y) * (player_head.y - fruits_pos[i].y);
			int enm_distance = (enemy_head.x - fruits_pos[i].x) * (enemy_head.x - fruits_pos[i].x) + (enemy_head.y - fruits_pos[i].y) * (enemy_head.y - fruits_pos[i].y);
			fruit_distance[i] = plr_distance - enm_distance;
		}

		// eneymy보다 내가 더 가까운 fruit 쪽으로

		bool** fruit_dir = new bool* [fruit_num];		// Up, Down, Left, Right
		for (int i = 0; i < fruit_num; i++) {
			fruit_dir[i] = new bool[4]{ false, false, false, false };

			if (fruits_pos[i].x > player_head.x) {
				fruit_dir[i][3] = true;
			}
			else if (fruits_pos[i].x < player_head.x) {
				fruit_dir[i][2] = true;
			}

			if (fruits_pos[i].y > player_head.y) {
				fruit_dir[i][1] = true;
			}
			else if (fruits_pos[i].y < player_head.y) {
				fruit_dir[i][0] = true;
			}
		}

		bool adjacent_body[4] = { false, false, false, false };
		
		for (Pos body_pos : player_snake->getPositions()) {		// 현재 head에 인접한 body가 있는지 check -> 그쪽으로 가면 안됨
			if (body_pos.x == player_head.x && body_pos.y == player_head.y - 1) {
				adjacent_body[0] = true;
				continue;
			}
			else if (body_pos.x == player_head.x && body_pos.y == player_head.y + 1) {
				adjacent_body[1] = true;
				continue;
			}
			else if (body_pos.y == player_head.y && body_pos.x == player_head.x - 1) {
				adjacent_body[2] = true;
				continue;
			}
			else if (body_pos.y == player_head.y && body_pos.x == player_head.x + 1) {
				adjacent_body[3] = true;
				continue;
			}
		}

		for (Pos enemy_pos : enemy_snake->getPositions()) {		// 현재 head에 인접한 enemy body가 있는지 check -> 그쪽으로 가면 안됨
			if (enemy_pos.x == player_head.x && enemy_pos.y == player_head.y - 1) {
				adjacent_body[0] = true;
				continue;
			}
			else if (enemy_pos.x == player_head.x && enemy_pos.y == player_head.y + 1) {
				adjacent_body[1] = true;
				continue;
			}
			else if (enemy_pos.y == player_head.y && enemy_pos.x == player_head.x - 1) {
				adjacent_body[2] = true;
				continue;
			}
			else if (enemy_pos.y == player_head.y && enemy_pos.y == player_head.x - 1) {
				adjacent_body[3] = true;
				continue;
			}
		}
		
		int* fruit_index_sorted = new int[fruit_num];
		for (int i = 0; i < fruit_num; i++) {
			fruit_index_sorted[i] = i;
		}

		for (int i = 0; i < fruit_num; i++) {
			for (int j = i + 1; j < fruit_num; j++) {
				if (fruit_distance[i] > fruit_distance[j]) {
					int temp = fruit_index_sorted[i];
					fruit_index_sorted[i] = fruit_index_sorted[j];
					fruit_index_sorted[j] = temp;
				}
			}
		}

		int go = -1;

		for (int i = 0; i < fruit_num; i++) {
			int idx = fruit_index_sorted[i];
			bool stop = false;
			for (go = 0; go < 4; go++) {
				if (fruit_dir[idx][go] == true && adjacent_body[go] == false) {
					stop = true;
					break;
				}
			}
			if (stop) {
				break;
			}
		}

		for (int i = 0; i < fruit_num; i++) {
			delete[] fruit_dir[i];
		}
		delete[] fruit_dir;
		delete[] fruits_pos;
		delete[] fruit_distance;
		delete[] fruit_index_sorted;

		if (go == 0) {
			return DrtN();
		}
		else if (go == 1) {
			return DrtS();
		}
		else if (go == 2) {
			return DrtW();
		}
		else if (go == 3) {
			return DrtE();
		}
		else {
			for (int dir = 0; dir < 4; dir++) {
				if (!adjacent_body[dir]) {
					if (dir == 0) {
						return DrtN();
					}
					else if (dir == 1) {
						return DrtS();
					}
					else if (dir == 2) {
						return DrtW();
					}
					else if (dir == 3) {
						return DrtE();
					}
				}
			}
		}
		return DrtE();
	}
}
