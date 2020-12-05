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

		for (int i = 0; i < 15; i++) {
			for (int j = 0; j < 15; j++) {
				map_checked[j][i] = 0;
			}
		}

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

		p_x = player_head.x;
		p_y = player_head.y;
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


		
		// 갇히는거 판단 (벽 제외)
		bool wall[4] = { false, false, false, false };
		if (dir_avail[3]) {
			if (!can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[3] = false;
			}
		}
		if (dir_avail[2]) {
			if (!can_go_outside(map, p_x - 1, p_y, wall)) {
				dir_avail[2] = false;
			}
		}
		if (dir_avail[1]) {
			if (!can_go_outside(map, p_x, p_y + 1, wall)) {
				dir_avail[1] = false;
			}
		}
		if (dir_avail[0]) {
			if (!can_go_outside(map, p_x, p_y - 1, wall)) {
				dir_avail[0] = false;
			}
		}
		
		
		// 위쪽 벽을 만났을 때
		if (p_y == 0) {
			// bool wall[4] = { true, false, false, true };		// 오른쪽 check
			wall[0] = true;
			wall[1] = false;
			wall[2] = false;
			wall[3] = true;
			if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
				bool test = can_go_outside(map, p_x + 1, p_y, wall);
				dir_avail[3] = false;
			}

			// bool wall[4] = { true, false, false, true };		// 왼쪽 check
			wall[0] = true;
			wall[1] = false;
			wall[2] = false;
			wall[3] = true;
			if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
				dir_avail[2] = false;
			}
		}

		// 아래쪽 벽을 만났을 때
		if (p_y == 14) {
			// bool wall[4] = { false, true, false, true };		// 오른쪽 check
			wall[0] = false;
			wall[1] = true;
			wall[2] = false;
			wall[3] = true;
			if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[3] = false;
			}

			// bool wall[4] = { false, true, true, false };		// 왼쪽 check
			wall[0] = false;
			wall[1] = true;
			wall[2] = true;
			wall[3] = false;
			if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
				dir_avail[2] = false;
			}
		}

		// 왼쪽 벽을 만났을 때
		if (p_x == 0) {
			// bool wall[4] = { true, false, true, false };		// 위쪽 check
			wall[0] = true;
			wall[1] = false;
			wall[2] = true;
			wall[3] = false;
			if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
				dir_avail[0] = false;
			}

			// bool wall[4] = { false, true, true, false };		// 아래쪽 check
			wall[0] = false;
			wall[1] = true;
			wall[2] = true;
			wall[3] = false;
			if (p_y < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[1] = false;
			}
		}

		// 오른쪽 벽을 만났을 때
		if (p_x == 14) {
			// bool wall[4] = { true, false, false, true };		// 위쪽 check
			wall[0] = true;
			wall[1] = false;
			wall[2] = false;
			wall[3] = true;
			if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
				dir_avail[0] = false;
			}

			// bool wall[4] = { false, true, false, true };		// 아래쪽 check
			wall[0] = false;
			wall[1] = true;
			wall[2] = false;
			wall[3] = true;
			if (p_y < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[1] = false;
			}
		}

		// 위쪽 장애물을 만났을 때
		if (p_y > 0 && p_y - 1 != 0) {
			wall[0] = false;
			wall[1] = true;
			wall[2] = false;
			wall[3] = true;
			if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[3] = false;
			}

			wall[0] = false;
			wall[1] = true;
			wall[2] = true;
			wall[3] = false;
			if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
				dir_avail[2] = false;
			}
		}

		// 아래쪽 장애물을 만났을 때
		if (p_y < 14 && p_y + 1 != 0) {
			wall[0] = true;
			wall[1] = false;
			wall[2] = false;
			wall[3] = true;
			if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[3] = false;
			}

			wall[0] = true;
			wall[1] = false;
			wall[2] = true;
			wall[3] = false;
			if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
				dir_avail[2] = false;
			}
		}

		// 왼쪽 장애물을 만났을 때
		if (p_x > 0 && p_x - 1 != 0) {
			wall[0] = true;
			wall[1] = false;
			wall[2] = false;
			wall[3] = true;
			if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
				dir_avail[0] = false;
			}

			wall[0] = false;
			wall[1] = true;
			wall[2] = false;
			wall[3] = true;
			if (p_y < 14 && !can_go_outside(map, p_x, p_y + 1, wall)) {
				dir_avail[1] = false;
			}
		}

		// 오른쪽 장애물을 만났을 때
		if (p_x < 14 && p_x + 1 != 0) {
			wall[0] = true;
			wall[1] = false;
			wall[2] = true;
			wall[3] = false;
			if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
				dir_avail[0] = false;
			}

			wall[0] = false;
			wall[1] = true;
			wall[2] = true;
			wall[3] = false;
			if (p_y < 14 && !can_go_outside(map, p_x, p_y + 1, wall)) {
				dir_avail[1] = false;
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

	bool MyPlayer::can_go_outside(int map[15][15], int x, int y, bool wall[4]) {	// 갇혔는지 판단 (벽 제외)
		if (map_checked[y][x] == 1) {
			return map_can_go[y][x];
		}
		if ((y == 0 && !wall[0]) || (y == 14 && !wall[1]) || (x == 0 && !wall[2]) || (x == 14 && !wall[3])) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
		else if (y == 0 || y == 14 || x == 0 || x == 14) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = false;
			return false;
		}
		/*
		if (x == p_x && y == p_y) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = false;
			return false;
		}
		*/
		map_checked[y][x] = 1;
		map_can_go[y][x] = false;

		bool go_up = true;
		bool go_down = true;
		bool go_left = true;
		bool go_right = true;


		if ((y > 0 && map[y - 1][x] != 0)/* || (x == p_x && y - 1 == p_y)*/) {
			go_up = false;
		}
		else {
			if (ex_check_dir != 'U') {
				ex_check_dir = 'D';
				go_up = can_go_outside(map, x, y - 1, wall);
			}
			else {
				go_up = false;
			}
		}

		if (go_up) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}


		if ((y < 14 && map[y + 1][x] != 0)/* || (x == p_x && y + 1 == p_y)*/) {
			go_down = false;
		}
		else {
			if (ex_check_dir != 'D') {
				ex_check_dir = 'U';
				go_down = can_go_outside(map, x, y + 1, wall);
			}
			else {
				go_down = false;
			}
		}

		if (go_down) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}


		if ((x > 0 && map[y][x - 1] != 0)/* || (x - 1 == p_x && y == p_y)*/) {
			go_left = false;
		}
		else {
			if (ex_check_dir != 'L') {
				ex_check_dir = 'R';
				go_left = can_go_outside(map, x - 1, y, wall);
			}
			else {
				go_left = false;
			}
		}

		if (go_left) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}


		if ((x < 14 && map[y][x + 1] != 0)/* || (x + 1 == p_x && y == p_y)*/) {
			go_right = false;
		}
		else {
			if (ex_check_dir != 'R') {
				ex_check_dir = 'L';
				go_right = can_go_outside(map, x + 1, y, wall);
			}
			else {
				go_right = false;
			}
		}

		if (go_right) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}

		if (!go_up && !go_down && !go_left && !go_right) {
			return false;
		}
		else {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
	}
}

