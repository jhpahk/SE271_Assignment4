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
		int map[15][15]{ {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0} };		// 2���� �迭 ������ map
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

		char p_dir;		// ������ �̵��� ����
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

		e_x = enemy_head.x;
		e_y = enemy_head.y;

		Pos fruits_pos[2];
		int fruit_distance[2];
		bool fruit_dir[2][4] = { {false, false, false, false}, {false, false, false, false} };

		for (int i = 0; i < 2; i++) {
			fruits_pos[i] = fruits[i]->getPositions()[0];
		}
		int player_to_fruit[2];
		int enemy_to_fruit[2];
		for (int i = 0; i < 2; i++) {		// ������ fruit������ �Ÿ� ���
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
		
		if (p_x == 14 ||map[p_y][p_x + 1] != 0) {			// �⺻������ 0�� �ƴ� �����δ� �� �� ����
			dir_avail[3] = false;
		}
		if (p_x == 0 || map[p_y][p_x - 1] != 0) {
			dir_avail[2] = false;
		}
		if (p_y == 14 || map[p_y + 1][p_x] != 0) {
			dir_avail[1] = false;
		}
		if (p_y == 0 || map[p_y - 1][p_x] != 0) {
			dir_avail[0] = false;
		}
		

		// �����°� �Ǵ� (�� ����)
		bool wall[4] = { false, false, false, false };

		for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
			for (int j = 0; j < 15; j++) {
				map_checked[j][i] = 0;
				ex_check_dir[j][i] = 'N';
			}
		}
		if (dir_avail[3]) {
			if (!can_go_outside(map, p_x + 1, p_y, wall)) {
				dir_avail[3] = false;
			}
		}

		for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
			for (int j = 0; j < 15; j++) {
				map_checked[j][i] = 0;
				ex_check_dir[j][i] = 'N';
			}
		}
		if (dir_avail[2]) {
			if (!can_go_outside(map, p_x - 1, p_y, wall)) {
				dir_avail[2] = false;
			}
		}

		for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
			for (int j = 0; j < 15; j++) {
				map_checked[j][i] = 0;
				ex_check_dir[j][i] = 'N';
			}
		}
		if (dir_avail[1]) {
			if (!can_go_outside(map, p_x, p_y + 1, wall)) {
				dir_avail[1] = false;
			}
		}

		for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
			for (int j = 0; j < 15; j++) {
				map_checked[j][i] = 0;
				ex_check_dir[j][i] = 'N';
			}
		}
		if (dir_avail[0]) {
			if (!can_go_outside(map, p_x, p_y - 1, wall)) {
				dir_avail[0] = false;
			}
		}
		

		// ���� ���� ������ ��
		if (p_y == 0 && p_dir == 'U') {
			// bool wall[4] = { true, false, false, true };		// ������ check
			if (dir_avail[3] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						ex_check_dir[j][i] = 'N';
						map_checked[j][i] = 0;
					}
				}
				if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
					dir_avail[3] = false;
				}
			}

			// bool wall[4] = { true, false, false, true };		// ���� check
			if (dir_avail[2] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						ex_check_dir[j][i] = 'N';
						map_checked[j][i] = 0;
					}
				}
				if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
					dir_avail[2] = false;
				}
			}
		}

		// �Ʒ��� ���� ������ ��
		if (p_y == 14 && p_dir == 'D') {
			// bool wall[4] = { false, true, false, true };		// ������ check
			if (dir_avail[3] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						ex_check_dir[j][i] = 'N';
						map_checked[j][i] = 0;
					}
				}
				if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
					dir_avail[3] = false;
				}
			}

			// bool wall[4] = { false, true, true, false };		// ���� check
			if (dir_avail[2] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						ex_check_dir[j][i] = 'N';
						map_checked[j][i] = 0;
					}
				}
				if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
					dir_avail[2] = false;
				}
			}
		}

		// ���� ���� ������ ��
		if (p_x == 0 && p_dir == 'L') {
			// bool wall[4] = { true, false, true, false };		// ���� check
			if (dir_avail[0] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
					dir_avail[0] = false;
				}
			}

			// bool wall[4] = { false, true, true, false };		// �Ʒ��� check
			if (dir_avail[1] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y < 14 && !can_go_outside(map, p_x, p_y + 1, wall)) {
					dir_avail[1] = false;
				}
			}
		}

		// ������ ���� ������ ��
		if (p_x == 14 && p_dir == 'R') {
			// bool wall[4] = { true, false, false, true };		// ���� check
			if (dir_avail[0] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
					dir_avail[0] = false;
				}
			}

			// bool wall[4] = { false, true, false, true };		// �Ʒ��� check
			if (dir_avail[1] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y < 14 && !can_go_outside(map, p_x, p_y + 1, wall)) {
					dir_avail[1] = false;
				}
			}
		}

		// ���� ��ֹ��� ������ ��
		if (p_y > 0 && map[p_y - 1][p_x] != 0 && p_dir == 'U') {
			if (dir_avail[3] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
					dir_avail[3] = false;
				}
			}

			if (dir_avail[2] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
					dir_avail[2] = false;
				}
			}
		}

		// �Ʒ��� ��ֹ��� ������ ��
		if (p_y < 14 && map[p_y + 1][p_x] != 0 && p_dir == 'D') {
			if (dir_avail[3] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_x < 14 && !can_go_outside(map, p_x + 1, p_y, wall)) {
					dir_avail[3] = false;
				}
			}

			if (dir_avail[2] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_x > 0 && !can_go_outside(map, p_x - 1, p_y, wall)) {
					dir_avail[2] = false;
				}
			}
		}

		// ���� ��ֹ��� ������ ��
		if (p_x > 0 && map[p_y][p_x - 1] != 0 && p_dir == 'L') {
			if (dir_avail[0] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
					dir_avail[0] = false;
				}
			}

			if (dir_avail[1] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y < 14 && !can_go_outside(map, p_x, p_y + 1, wall)) {
					dir_avail[1] = false;
				}
			}
		}

		// ������ ��ֹ��� ������ ��
		if (p_x < 14 && map[p_y][p_x + 1] != 0 && p_dir == 'R') {
			if (dir_avail[0] == true) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y > 0 && !can_go_outside(map, p_x, p_y - 1, wall)) {
					dir_avail[0] = false;
				}
			}

			if (dir_avail[1] == true) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = true;
				wall[3] = false;
				for (int i = 0; i < 15; i++) {		// map_checked �ʱ�ȭ
					for (int j = 0; j < 15; j++) {
						map_checked[j][i] = 0;
						ex_check_dir[j][i] = 'N';
					}
				}
				if (p_y < 14 && !can_go_outside(map, p_x, p_y + 1, wall)) {
					dir_avail[1] = false;
				}
			}
		}

		// ��뿡�� ���ݴ��ϴ� �� �����ؼ� ȸ��
		
		if (p_y > 0 && p_dir == 'U') {		// up
			if (p_x < 14 && dir_avail[3] == true && map[p_y - 1][p_x + 1] == 2) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = true;
				wall[3] = false;
				if (!can_go_outside(map, p_x - 1, p_y, wall)) {
					dir_avail[2] = false;
				}
				if (dir_avail[0]|| dir_avail[1] || dir_avail[2]) {
					dir_avail[3] = false;
				}
			}
			if (p_x > 0 && dir_avail[2] == true && map[p_y - 1][p_x - 1] == 2) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				if (!can_go_outside(map, p_x + 1, p_y, wall)) {
					dir_avail[3] = false;
				}
				if (dir_avail[0] == true || dir_avail[1] == true || dir_avail[3]) {
					dir_avail[2] = false;
				}
			}
		}
		if (p_y < 14 && p_dir == 'D') {		// down
			if (p_x < 14 && dir_avail[3] == true && map[p_y + 1][p_x + 1] == 2) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = true;
				wall[3] = false;
				if (!can_go_outside(map, p_x - 1, p_y, wall)) {
					dir_avail[2] = false;
				}
				if (dir_avail[0] || dir_avail[1] || dir_avail[2]) {
					dir_avail[3] = false;
				}
			}
			if (p_x > 0 && dir_avail[2] == true && map[p_y + 1][p_x - 1] == 2) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				if (!can_go_outside(map, p_x + 1, p_y, wall)) {
					dir_avail[3] = false;
				}
				if (dir_avail[0] || dir_avail[1] || dir_avail[3]) {
					dir_avail[2] = false;
				}
			}
		}
		if (p_x > 0 && p_dir == 'L') {		// left
			if (p_y < 14 && dir_avail[1] == true && map[p_y + 1][p_x - 1] == 2) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = false;
				wall[3] = true;
				if (!can_go_outside(map, p_x, p_y - 1, wall)) {
					dir_avail[0] = false;
				}
				if (dir_avail[0] || dir_avail[3] || dir_avail[2]) {
					dir_avail[1] = false;
				}
			}
			if (p_y > 0 && dir_avail[0] == true && map[p_y - 1][p_x - 1] == 2) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				if (!can_go_outside(map, p_x, p_y + 1, wall)) {
					dir_avail[1] = false;
				}
				if (dir_avail[3] || dir_avail[1] || dir_avail[2]) {
					dir_avail[0] = false;
				}
			}
		}
		if (p_x > 14 && p_dir == 'R') {		// right
			if (p_y < 14 && dir_avail[1] == true && map[p_y + 1][p_x + 1] == 2) {
				wall[0] = true;
				wall[1] = false;
				wall[2] = true;
				wall[3] = false;
				if (!can_go_outside(map, p_x, p_y - 1, wall)) {
					dir_avail[0] = false;
				}
				if (dir_avail[0] || dir_avail[3] || dir_avail[2]) {
					dir_avail[1] = false;
				}
			}
			if (p_y > 0 && dir_avail[0] == true && map[p_y - 1][p_x + 1] == 2) {
				wall[0] = false;
				wall[1] = true;
				wall[2] = false;
				wall[3] = true;
				if (!can_go_outside(map, p_x, p_y + 1, wall)) {
					dir_avail[1] = false;
				}
				if (dir_avail[0] || dir_avail[1] || dir_avail[2]) {
					dir_avail[3] = false;
				}
			}
		}
		

		int sorted_fidx[2] = { 0, 1 };						// ���� idx�� ����� ������� ����
		if ((fruit_distance[0] < 0 && fruit_distance[1] < 0 && player_to_fruit[1] < player_to_fruit[0]) || ((fruit_distance[0] > 0 || fruit_distance[1] > 0) && (fruit_distance[0] > fruit_distance[1]))) {
			sorted_fidx[0] = 1;
			sorted_fidx[1] = 0;
		}
		if (fruit_distance[1] <= 312) {							// fruit taking�� ���ؼ� ����
			for (int i = 0; i < 2; i++) {						// fruit �ִ� �������� �� �� ������ ����
				int idx = sorted_fidx[i];
				if (fruit_dir[idx][1] == true && dir_avail[1] == true && p_dir != 'U') {
					return DrtS();
				}
				else if (fruit_dir[idx][2] == true && dir_avail[2] == true && p_dir != 'R') {
					return DrtW();
				}
				else if (fruit_dir[idx][0] == true && dir_avail[0] == true && p_dir != 'D') {
					return DrtN();
				}
				else if (fruit_dir[idx][3] == true && dir_avail[3] == true && p_dir != 'L') {
					return DrtE();
				}
				else {
					if (dir_avail[0] == true && p_dir != 'D') {
						return DrtN();
					}
					else if (dir_avail[3] == true && p_dir != 'L') {
						return DrtE();
					}
					else if (dir_avail[1] == true && p_dir != 'U') {
						return DrtS();
					}
					else if (dir_avail[2] == true && p_dir != 'R') {
						return DrtW();
					}
					else {
						if (p_x < 14 && map[p_y][p_x + 1] == 0) {
							return DrtE();
						}
						else if (p_x > 0 && map[p_y][p_x - 1] == 0) {
							return DrtW();
						}
						else if (p_y < 14 && map[p_y + 1][p_x] == 0) {
							return DrtS();
						}
						else {
							return DrtN();
						}
					}
				}
			}
		}
		else {
			if (dir_avail[0] == true && p_dir != 'D') {
				return DrtN();
			}
			else if (dir_avail[3] == true && p_dir != 'L') {
				return DrtE();
			}
			else if (dir_avail[1] == true && p_dir != 'U') {
				return DrtS();
			}
			else if (dir_avail[2] == true && p_dir != 'R') {
				return DrtW();
			}
			else {
				if (p_x < 14 && map[p_y][p_x + 1] == 0) {
					return DrtE();
				}
				else if (p_x > 0 && map[p_y][p_x - 1] == 0) {
					return DrtW();
				}
				else if (p_y < 14 && map[p_y + 1][p_x] == 0) {
					return DrtS();
				}
				else {
					return DrtN();
				}
			}
		}
	}

	bool MyPlayer::can_go_outside(int map[15][15], int x, int y, bool wall[4]) {	// �������� �Ǵ�

		if (x > 14 || x < 0 || y > 14 || y < 0) {
			return false;
		}

		bool go_up = false;
		bool go_down = false;
		bool go_left = false;
		bool go_right = false;

		bool up_checked = false;
		bool down_checked = false;
		bool left_checked = false;
		bool right_checked = false;

		if (map_checked[y][x] == 1) {
			return map_can_go[y][x];
		}
		if ((y == 0 && !wall[0]) || (y == 14 && !wall[1]) || (x == 0 && !wall[2]) || (x == 14 && !wall[3])) {
			if (y == 0) {
				go_up = true;
				up_checked = true;
			}
			if (y == 14) {
				go_down = true;
				down_checked = true;
			}
			if (x == 0) {
				go_left = true;
				left_checked = true;
			}
			if (x == 14) {
				go_right = true;
				right_checked = true;
			}
		}
		else if (y == 0 || y == 14 || x == 0 || x == 14) {
			if (y == 0) {
				go_up = false;
				up_checked = true;
			}
			if (y == 14) {
				go_down = false;
				down_checked = true;
			}
			if (x == 0) {
				go_left = false;
				left_checked = true;
			}
			if (x == 14) {
				go_right = false;
				right_checked = true;
			}
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

		if (go_up) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
		else if (!up_checked) {
			if ((y > 0 && map[y - 1][x] != 0)/* || (x == p_x && y - 1 == p_y)*/) {
				go_up = false;
			}
			else {
				if (ex_check_dir[y][x] != 'D') {
					ex_check_dir[y - 1][x] = 'U';
					go_up = can_go_outside(map, x, y - 1, wall);
				}
				else {
					go_up = false;
				}
			}
		}

		if (go_down) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
		else if (!down_checked) {
			if ((y < 14 && map[y + 1][x] != 0)/* || (x == p_x && y + 1 == p_y)*/) {
				go_down = false;
			}
			else {
				if (ex_check_dir[y][x] != 'U') {
					ex_check_dir[y + 1][x] = 'D';
					go_down = can_go_outside(map, x, y + 1, wall);
				}
				else {
					go_down = false;
				}
			}
		}

		if (go_left) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
		else if (!left_checked) {
			if ((x > 0 && map[y][x - 1] != 0)/* || (x - 1 == p_x && y == p_y)*/) {
				go_left = false;
			}
			else {
				if (ex_check_dir[y][x] != 'R') {
					ex_check_dir[y][x - 1] = 'L';
					go_left = can_go_outside(map, x - 1, y, wall);
				}
				else {
					go_left = false;
				}
			}
		}

		if (go_right) {
			map_checked[y][x] = 1;
			map_can_go[y][x] = true;
			return true;
		}
		else if (!right_checked) {
			if ((x < 14 && map[y][x + 1] != 0)/* || (x + 1 == p_x && y == p_y)*/) {
				go_right = false;
			}
			else {
				if (ex_check_dir[y][x] != 'L') {
					ex_check_dir[y][x + 1] = 'R';
					go_right = can_go_outside(map, x + 1, y, wall);
				}
				else {
					go_right = false;
				}
			}
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

