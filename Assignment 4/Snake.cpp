////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Snake.h"

#include "Commons.h"

namespace snake_arena {
	Snake::Snake(const Pos& pos, const Direction& direction, int length) :
		direction(direction), length(length) {
		body.push_back(pos);
	}

	bool Snake::hit(const Pos& pos) const {
		return (std::find(body.begin(), body.end(), pos) != body.end());
	}

	std::vector<Pos> Snake::getPositions() const {
		return { body.begin(), body.end() }; // conver it to the vector
	}

	int Snake::getLength() const {
		return length;
	}

	Direction Snake::getDirection() const {
		return direction;
	}


	bool Snake::isCrashed() const {
		return is_crashed;
	}

	Pos Snake::move() {
		Pos newHead = getNextHead();

		// If the snake grows to the maximum length
		if (body.size() == length) { 
			body.pop_back();
		}

		// Add the new head
		body.push_front(newHead); 

		return newHead;
	}

	bool Snake::setDirection(const Direction& _direction) {
		// Check if it's the opposite direction
		if (direction.dx * -1 == _direction.dx && direction.dy * -1 == _direction.dy) {
			return false; // The snake cannot move toward 180 degree
		}

		direction = _direction;
		return true;
	}

	void Snake::grow() {
		++length;
	}


	Pos Snake::getNextHead() {
		return body[0] + direction;
	}

	void Snake::setCrashed() {
		is_crashed = true;
	}

}