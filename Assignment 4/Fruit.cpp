////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Fruit.h"

namespace snake_arena {
	Fruit::Fruit(const Pos& pos) : Pos(pos) { }

	bool Fruit::hit(const Pos& pos) const {
		return (this->x == pos.x && this->y == pos.y);
	}

	std::vector<Pos> Fruit::getPositions() const {
		std::vector<Pos> new_vector;
		new_vector.push_back(Pos(this->x, this->y));
		return new_vector;
	}
}

