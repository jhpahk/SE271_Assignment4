#include "Commons.h"

#include <cassert>

namespace snake_arena {
	Pos::Pos(int x, int y) : x(x), y(y) { }

	Pos Pos::operator+(const Direction& action) const {
		return Pos(x + action.dx, y + action.dy);
	}

	Pos Pos::operator-(const Direction& action) const {
		return Pos(x - action.dx, y - action.dy);
	}

	bool Pos::operator==(const Pos& p) const {
		return (x == p.x) && (y == p.y);
	}

	bool Pos::operator!=(const Pos& p) const {
		return (x != p.x) || (y != p.y);
	}


	Direction::Direction(int dx, int dy) : dx(dx), dy(dy) { 
		if (!(dx <= 1 && dx >= -1))
			assert(false);
		if (!(dy <= 1 && dy >= -1))
			assert(false);
	}

	Pos Direction::operator+(const Pos& pos) const {
		return Pos(dx + pos.x, dy + pos.y);
	}

	Pos Direction::operator-(const Pos& pos) const {
		return Pos(dx - pos.x, dy - pos.y);
	}

	bool Direction::operator==(const Direction& a) const {
		return (dx == a.dx) && (dy == a.dy);
	}

	bool Direction::operator!=(const Direction& a) const {
		return (dx != a.dx) || (dy != a.dy);
	}

}
