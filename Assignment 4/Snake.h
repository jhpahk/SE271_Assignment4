#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "Unit.h"

#include <vector>
#include <deque>


namespace snake_arena {
    class Snake final : public Unit {
    public:
		/**
		*   \brief Constructor
		*   \param pos: the starting position of the snake head
		*   \param direction: the initial direction of the snake
		*   \param length: the length of the snake
		**/
        Snake(const Pos& pos, const Direction& direction, int length);

		/**
		*   \brief Check whether the position hits the snake body
		*   \param Pos: the position to check
		*   \return true if hit, false otherwise 
		**/
        virtual bool hit(const Pos& pos) const override;

		/**
		*   \brief Get all the positions that the snake body occupies
		*   \return Vector of the body positions
		**/
        virtual std::vector<Pos> getPositions() const override;

		/**
		*   \brief Get length
		*	This could be different from the length of the body
		*	e.g., right after the game start or right after eating a fruit 
		*   \return the length of the body
		**/
        int getLength() const;

		/**
		*   \brief Get direction
		*   \return the direction of the snake
		**/
        Direction getDirection() const;

		/**
		*   \brief Get if crashed in the last move
		*   \return the length of the body
		**/
        bool isCrashed() const;

	private:
		// Note for students:
		// Using friend too much is not a good habbit.
		// We use here to prevent undesired/illegal code and game modifications.
		// e.g., you cannot use these functions to design your strategy.
		// In the usual situtaiton, the following functions should be public
		// without using the friend keyword.
		friend class Environment;

		/**
		*   \brief Move the body toward the direction
		*   \return the new head position of the moved snake
		**/
		Pos move();

		/**
		*   \brief Set the direction of the snake
		*   \return true if it's a valid direction and set up
		**/
		bool setDirection(const Direction& direction);

		/**
		*   \brief Get the head position if moved toward direction
		**/
		Pos getNextHead();

		/**
		*   \brief Grow the snake, i.e., length += 1
		**/
		void grow();

		/**
		*   \brief Notify the snake hits somewhere bad
		**/
		void setCrashed();

	private:
		std::deque<Pos> body;
		Direction direction;
		int length;
		bool is_crashed = false;
    };
}
