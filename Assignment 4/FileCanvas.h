#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
// Write texts into a file
// This class is platform-independent.
////////////////////////////////////////////////////////////////////////////////

#include "Canvas.h"

#include <string>
#include <sstream>

namespace snake_arena {
    // Canvas to draw lines into the file
	class FileCanvas : public Canvas {
	public:
		/**
		*   \brief Constructor
		*   \param filename: file name
		**/
		FileCanvas(const char* filename);


		// Destructor
		virtual ~FileCanvas();

		/**
		*   \brief Write a new line to a buffer 
		*   \param line: null-terminated character string.
        *   \return return true it succeeds 
		**/
		virtual bool addLine(const char* line);

		/**
		*   \brief Write the buffered texts into the file.
		**/
		virtual void draw();

	private:
		int frame;
		std::string filename;
		std::stringstream outstream;
	};
}

