////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "FileCanvas.h"

#include <fstream>

namespace snake_arena {
	FileCanvas::FileCanvas(const char* filename) : 
		frame(0), filename(filename) {
		std::ofstream fout(filename); // Clear file content
		fout.close();
	}

	FileCanvas::~FileCanvas() {
	}

	bool FileCanvas::addLine(const char* line) {
		outstream << line << std::endl;
		return true;
	}

	void FileCanvas::draw() {
		std::ofstream fout(filename, std::ios_base::app);
		fout << "Frame " << frame++ << std::endl;
		fout << outstream.str();
        fout.close();

		outstream.str(std::string()); // Clear stream
	}
}

