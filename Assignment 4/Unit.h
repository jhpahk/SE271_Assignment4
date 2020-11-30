#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Commons.h"

#include <vector>

namespace snake_arena {
	// Unit interface class in the map 
	class Unit {
	public:
		virtual ~Unit() {};
		virtual bool hit(const Pos& pos) const = 0;
        virtual std::vector<Pos> getPositions() const = 0;
	};
}
