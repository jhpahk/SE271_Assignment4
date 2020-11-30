#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Unit.h"
#include "Commons.h"

namespace snake_arena {
	// Fruit Unit class
	class Fruit final : public Unit, public Pos {
	public:
		// Constructor with fruit position
		Fruit(const Pos& pos);

		// check whether the position hits this fruit
		virtual bool hit(const Pos& pos) const override;

		// return the single-element vector containing the fruit position
		virtual std::vector<Pos> getPositions() const override;
	};
}
