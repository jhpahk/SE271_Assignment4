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
		mapsize = map_size;
	}

	// Destructor
	MyPlayer::~MyPlayer() {

	}

	// Your function to primarily implement
	Direction MyPlayer::selectDirection(int turn, Snake* player_snake, Snake* enemy_snake, std::vector<Fruit*> fruits) {

		int player_len = player_snake->getLength();
		Pos player_head = player_snake->getPositions()[0];
		int p_tail[2];

		int idx_count = 0;
		int map[15][15]{ {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };		// 2차원 배열 형태의 map
		for (Pos player_pos : player_snake->getPositions()) {		// Player: 1
			idx_count++;
			map[player_pos.y][player_pos.x] = 1;
			if (idx_count == player_len) {
				p_tail[0] = player_pos.x;
				p_tail[1] = player_pos.y;
			}
		}
		for (Pos enemy_pos : enemy_snake->getPositions()) {			// Enemy: 2
			map[enemy_pos.y][enemy_pos.x] = 2;
		}
		/*for (int i = 0; i < 2; i++) {
			for (Pos fruit_pos : fruits[i]->getPositions()) {		// Fruits: 3
				map[fruit_pos.y][fruit_pos.x] = 3;
			}
		}*/

		int p_x = player_head.x;
		int p_y = player_head.y;
		char p_dir;		// 직전에 이동한 방향
		if (player_snake->getDirection().dy == -1) {
			p_dir = 'U';
		}
		else if (player_snake->getDirection().dy == 1) {
			p_dir = 'D';
		}
		else if (player_snake->getDirection().dx == -1) {
			p_dir = 'L';
		}
		else if (player_snake->getDirection().dx == 1) {
			p_dir = 'R';
		}

		int enemy_len = enemy_snake->getLength();
		Pos enemy_head = enemy_snake->getPositions()[0];

		Pos fruits_pos[2];
		int fruit_distance[2];
		bool fruit_dir[2][4] = { {false, false, false, false}, {false, false, false, false} };

		for (int i = 0; i < 2; i++) {
			fruits_pos[i] = fruits[i]->getPositions()[0];
		}
		int player_to_fruit[2];
		int enemy_to_fruit[2];
		for (int i = 0; i < 2; i++) {		// 각각의 fruit까지의 거리 계산
			player_to_fruit[i] = (fruits_pos[i].x - p_x) * (fruits_pos[i].x - p_x) + (fruits_pos[i].y - p_y) * (fruits_pos[i].y - p_y);
			enemy_to_fruit[i] = (fruits_pos[i].x - enemy_head.x) * (fruits_pos[i].x - enemy_head.x) + (fruits_pos[i].y - enemy_head.y) * (fruits_pos[i].y - enemy_head.y);
			fruit_distance[i] = player_to_fruit[i] - enemy_to_fruit[i];
		}
		for (int i = 0; i < 2; i++) {						// UP, DOWN, LEFT, RIGHT
			if (fruits_pos[i].x > p_x) {
				fruit_dir[i][3] = true;
			}
			else if (fruits_pos[i].x < p_x) {
				fruit_dir[i][2] = true;
			}

			if (fruits_pos[i].y > p_y) {
				fruit_dir[i][1] = true;
			}
			else if (fruits_pos[i].y < p_y) {
				fruit_dir[i][0] = true;
			}
		}

		bool dir_avail[4] = { true, true, true, true };		// UP, DOWN, LEFT, RIGHT
		
		if (map[p_y][p_x + 1] != 0 || p_x == 14) {			// 기본적으로 0이 아닌 곳으로는 갈 수 없다
			dir_avail[3] = false;
		}
		if (map[p_y][p_x - 1] != 0 || p_x == 0) {
			dir_avail[2] = false;
		}
		if (map[p_y + 1][p_x] != 0 || p_y == 14) {
			dir_avail[1] = false;
		}
		if (map[p_y - 1][p_x] != 0 || p_y == 0) {
			dir_avail[0] = false;
		}
		
		
		// Box 안으로 들어가는 것 방지
		if (p_y > 0 && p_x > 0 && p_x < 14 && p_dir == 'U' && map[p_y - 1][p_x] != 0) {		// 위로 가다 막혔을 때
			int count = 0;
			for (int y = p_y - 1; y < 15; y++) {		// 오른쪽으로 못가는 경우
				if (map[y][p_x + 1] != 0) {
					count++;
				}
				if (count == 2) {
					dir_avail[3] = false;
					break;
				}
				if (map[y][p_x - 1] != 0) {
					if (y != p_y - 1) {
						break;
					}
					break;
				}
			}

			count = 0;
			for (int y = p_y - 1; y < 15; y++) {		// 왼쪽으로 못가는 경우
				if (map[y][p_x - 1] != 0) {
					count++;
				}
				if (count == 2) {
					dir_avail[2] = false;
					break;
				}
				if (map[y][p_x + 1] != 0) {
					if (y != p_y - 1) {
						break;
					}
					break;
				}
			}
		}

		std::vector<int> ex_obs_pos;
		std::vector<int> cur_obs_pos;
		int ex_obs_count = 0;
		int cur_obs_count = 0;
		int temp_obs_count = 0;
		int cur_y_up = p_y;
		int cur_y_down = p_y;
		bool cannot_go = true;

		// Can go right?
		if (p_dir != 'L') {
			for (int x = p_x; x < 14; x++) {
				cur_y_up = p_y;
				cur_y_down = p_y;
				if (map[p_y][x] != 0) {		// 검사 종료 조건 -> 맞은편 벽에 도달
					for (int y = p_y; y >= 0; y--) {
						if (map[y][x] == 0) {
							cannot_go = false;
							break;
						}
						for (int y_check = 0; y_check < ex_obs_count; y_check++) {
							if (y == ex_obs_pos[y_check] + 1) {
								break;
							}
						}
						if (!cannot_go) {
							break;
						}
					}
					for (int y = p_y; y < 15; y++) {
						if (map[y][x] == 0) {
							cannot_go = false;
							break;
						}
						for (int y_check = 0; y_check < ex_obs_count; y_check++) {
							if (y == ex_obs_pos[y_check] - 1) {
								break;
							}
						}
						if (!cannot_go) {
							break;
						}
					}
					if (cannot_go) {
						dir_avail[3] = false;
					}
				}
				cur_obs_count = 0;
				cur_obs_pos.clear();
				if (x == p_x) {
					while (ex_obs_count < 2) {
						cur_y_up++;
						cur_y_down--;
						if (x < 14 && map[cur_y_up][x + 1] != 0 || cur_y_up == 0) {
							ex_obs_pos.push_back(cur_y_up + 1);
							ex_obs_count++;
						}
						if (x < 14 && map[cur_y_down][x + 1] != 0 || cur_y_down == 14) {
							ex_obs_pos.push_back(cur_y_down - 1);
							ex_obs_count++;
						}
					}
					continue;
				}
				for (int obs = 0; obs < ex_obs_count; obs++) {
					temp_obs_count = 0;
					if (ex_obs_pos[obs] > 0 && map[ex_obs_pos[obs] - 1][x] != 0) {
						cur_obs_pos.push_back(ex_obs_pos[obs] - 1);
						cur_obs_count++;
						temp_obs_count++;
					}
					if (ex_obs_pos[obs] < 14 && map[ex_obs_pos[obs] + 1][x] != 0) {
						cur_obs_pos.push_back(ex_obs_pos[obs] + 1);
						cur_obs_count++;
						temp_obs_count++;
					}
					if (temp_obs_count < 2) {
						cannot_go = false;
						break;
					}
				}
				if (!cannot_go) {
					break;
				}
				else {
					ex_obs_count = cur_obs_count;
					ex_obs_pos = cur_obs_pos;
				}
			}
		}

		cannot_go = true;
		cur_obs_pos.clear();
		ex_obs_pos.clear();
		cur_obs_count = 0;
		ex_obs_count = 0;

		// Can go left?
		if (p_dir != 'R') {
			for (int x = p_x; x >= 0; x--) {
				cur_y_up = p_y;
				cur_y_down = p_y;
				if (map[p_y][x] != 0) {		// 검사 종료 조건 -> 맞은편 벽에 도달
					for (int y = p_y; y >= 0; y--) {
						if (map[y][x] == 0) {
							cannot_go = false;
							break;
						}
						for (int y_check = 0; y_check < ex_obs_count; y_check++) {
							if (y == ex_obs_pos[y_check] + 1) {
								break;
							}
						}
						if (!cannot_go) {
							break;
						}
					}
					for (int y = p_y; y < 15; y++) {
						if (map[y][x] == 0) {
							cannot_go = false;
							break;
						}
						for (int y_check = 0; y_check < ex_obs_count; y_check++) {
							if (y == ex_obs_pos[y_check] - 1) {
								break;
							}
						}
						if (!cannot_go) {
							break;
						}
					}
					if (cannot_go) {
						dir_avail[3] = false;
					}
				}
				cur_obs_count = 0;
				cur_obs_pos.clear();
				if (x == p_x) {
					while (ex_obs_count < 2) {
						cur_y_up++;
						cur_y_down--;
						if (p_x > 0 && map[cur_y_up][x - 1] != 0 || cur_y_up == 0) {
							ex_obs_pos.push_back(cur_y_up + 1);
							ex_obs_count++;
						}
						if (p_x > 0 && map[cur_y_down][x - 1] != 0 || cur_y_down == 14) {
							ex_obs_pos.push_back(cur_y_down - 1);
							ex_obs_count++;
						}
					}
					continue;
				}
				for (int obs = 0; obs < ex_obs_count; obs++) {
					temp_obs_count = 0;
					if (ex_obs_pos[obs] > 0 && map[ex_obs_pos[obs] - 1][x] != 0) {
						cur_obs_pos.push_back(ex_obs_pos[obs] - 1);
						cur_obs_count++;
						temp_obs_count++;
					}
					if (ex_obs_pos[obs] < 14 && map[ex_obs_pos[obs] + 1][x] != 0) {
						cur_obs_pos.push_back(ex_obs_pos[obs] + 1);
						cur_obs_count++;
						temp_obs_count++;
					}
					if (temp_obs_count < 2) {
						cannot_go = false;
						break;
					}
				}
				if (!cannot_go) {
					break;
				}
				else {
					ex_obs_count = cur_obs_count;
					ex_obs_pos = cur_obs_pos;
				}
			}
		}


		int sorted_fidx[2] = { 0, 1 };						// 과일 idx를 가까운 순서대로 보관
		if ((fruit_distance[0] < 0 && fruit_distance[1] < 0 && player_to_fruit[1] < player_to_fruit[0]) || ((fruit_distance[0] > 0 || fruit_distance[1] > 0) && (fruit_distance[0] > fruit_distance[1]))) {
			sorted_fidx[0] = 1;
			sorted_fidx[1] = 0;
		}
		
		for (int i = 0; i < 2; i++) {						// fruit 있는 방향으로 갈 수 있으면 간다
			int idx = sorted_fidx[i];
			if (fruit_dir[idx][0] == true && dir_avail[0] == true && p_dir != 'D') {
				return DrtN();
			}
			else if (fruit_dir[idx][1] == true && dir_avail[1] == true && p_dir != 'U') {
				return DrtS();
			}
			else if (fruit_dir[idx][2] == true && dir_avail[2] == true && p_dir != 'R') {
				return DrtW();
			}
			else if (fruit_dir[idx][3] == true && dir_avail[3] == true && p_dir != 'L') {
				return DrtE();
			}
		}

		// fruit 방향으로 갈 수 없을 때
		if (dir_avail[0] == true && p_dir != 'D') {
			return DrtN();
		}
		else if (dir_avail[1] == true && p_dir != 'U') {
			return DrtS();
		}
		else if (dir_avail[2] == true && p_dir != 'R') {
			return DrtW();
		}
		else if (dir_avail[3] == true && p_dir != 'L') {
			return DrtE();
		}

		// 갈 수 있는 방향이 없을 때 -> Game Over, 아무 방향으로 이동
		return DrtN();
	}
}
