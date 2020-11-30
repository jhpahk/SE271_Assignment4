#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
// Draw texts into the console
// This class is platform-dependent.
// The current code is implemented and tested in VS2019 using Console mode.
////////////////////////////////////////////////////////////////////////////////

#include "Canvas.h"

#include <vector>

namespace snake_arena {
    class TextPixel;

    // Canvas to draw frames into the console
    class ConsoleCanvas final : public Canvas {
    public:
        /**
		*   \brief Constructor
		*   \param width: frame width
		*   \param height: frame height
		**/
        ConsoleCanvas(size_t width, size_t height);

        // Destructor
        virtual ~ConsoleCanvas() override;


		/**
		*   \brief Add a new line in the current canvas
		*   \param line: null-terminated character string.
        *   The length should be smaller than width.
        *   \return return if it succeeds 
		**/
        virtual bool addLine(const char* line) override;

		/**
		*   \brief Draw the current canvas frame and pause for sleep_millisecond
        *   \param sleep_millisecond: time to sleep in ms
		**/
        virtual void draw(int sleep_millisecond);

		/**
		*   \brief Draw the current canvas frame and pause for 50 ms
		**/
        virtual void draw() override { draw(def_sleep_millisecond); };

		/**
		*   \brief Set the default sleep time called in draw()
		*   \param default_sleep_ms: the sleep time
		**/
        virtual void setDefaultSleepTime(int sleep_millisecond) {
            def_sleep_millisecond = sleep_millisecond;
        }


    private:
        int width; // Frame width 
        int height; // Frame height
        int def_sleep_millisecond = 50; // default sleep time

        // Double buffering
        int line_index = 0; // line index of current buffer
        char* prev_buffer = nullptr; // buffer already drawn
        char* curr_buffer = nullptr; // buffer currently filled

    private:
        size_t convertCoord(int x, int y);
        std::vector<TextPixel> _getFrameDifference();
    };

	// A simple class to represent a pixel on a certain location
    class TextPixel {
    public:
        TextPixel(int x, int y, char c) : x(x), y(y), c(c) {}
        int x; int y; char c;
    };
}