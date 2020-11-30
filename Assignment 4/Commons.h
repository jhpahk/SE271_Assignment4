#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

// Common classes for position and direction

#include <vector>

namespace snake_arena {
	class Direction;

	// 2D Position
	class Pos {
	public:
		Pos() {};
		Pos(int x, int y);
		Pos operator+(const Direction&) const;
		Pos operator-(const Direction&) const;
		bool operator==(const Pos&) const;
		bool operator!=(const Pos&) const;

	public:
		int x = 0, y = 0;
	};

	// Direction. You may want to use DrtN, DrtS, DrtE, DrtW
	class Direction {
	public:
		Direction() {};
		Direction(int dx, int dy);
		Pos operator+(const Pos&) const;
		Pos operator-(const Pos&) const;
		bool operator==(const Direction&) const;
		bool operator!=(const Direction&) const;

	public:
		int dx = 0;
		int dy = 0;
	};

	// Note for advanced students:
	// The followings could be singleton classes,
	// but one may want to create new instances to design their strategy.

	class DrtN : public Direction { public: DrtN() : Direction(0, -1) {} }; // North
	class DrtS : public Direction { public: DrtS() : Direction(0, +1) {} }; // South
	class DrtE : public Direction { public: DrtE() : Direction(+1, 0) {} }; // East
	class DrtW : public Direction { public: DrtW() : Direction(-1, 0) {} }; // West

	// Check whether an element exists in the vector
	template<typename T>
	bool exists(const std::vector<T>& v, const T& value) {
		return (std::find(v.begin(), v.end(), value) != v.end());
	}

	// Append the src vector into the dest vector
	template<typename T>
	void appendVector(std::vector<T>& dest, const std::vector<T>& src) {
		dest.insert(dest.end(), src.begin(), src.end());
	}

};
