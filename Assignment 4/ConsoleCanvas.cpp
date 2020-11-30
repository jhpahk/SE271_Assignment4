////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

#include "ConsoleCanvas.h"

#include <iostream>
#include <Windows.h>

namespace snake_arena {
    ConsoleCanvas::ConsoleCanvas(size_t width, size_t height) :
        width(width), height(height) {
        prev_buffer = new char[width * height];
        memset(prev_buffer, 0, width * height);
        curr_buffer = new char[width * height];
        memset(curr_buffer, 0, width * height);
    }

    ConsoleCanvas::~ConsoleCanvas() {
        delete[] prev_buffer;
        delete[] curr_buffer;
    }

    bool ConsoleCanvas::addLine(const char* line) {
        int n_line = strlen(line);

        // Overflow check
        if (n_line >= width || line_index == height) {
            return false;
        }

        char* buf_pos = &curr_buffer[line_index * width];
        memset(buf_pos, 0, width); // Fill zeros to handle lines shorter than the width
        memcpy(buf_pos, line, n_line);
        ++line_index;

        return true;
    }

    // https://stackoverflow.com/questions/34842526/update-console-without-flickering-c
    static void setCursorPosition(int x, int y) {
        static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        std::cout.flush();
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(hOut, coord);
    }

    void ConsoleCanvas::draw(int sleep_millisecond) {
        // Fill empty lines heights
        while (addLine("")) {};

        // Compute pixel difference
        std::vector<TextPixel> results = _getFrameDifference();

        // Update changed pixels only
        for (auto& pixel : results) {
            setCursorPosition(pixel.x, pixel.y);
            std::cout.write(&pixel.c, 1);
        }
        setCursorPosition(0, height);

        // Flip buffers
        char* tmp = prev_buffer;
        prev_buffer = curr_buffer;
        curr_buffer = tmp;

        // Change index to start a new frame for the next add
        line_index = 0;

        // Sleep to keep FPS
        Sleep(sleep_millisecond);
    }


    size_t ConsoleCanvas::convertCoord(int x, int y) {
        return x + y * width;
    }

    std::vector<TextPixel> ConsoleCanvas::_getFrameDifference() {
        // Pixels changed between the two buffers will be stored here
        std::vector<TextPixel> pixel_changes;

        for (auto y = 0; y < height; ++y) {
            for (auto x = 0; x < width; ++x) {
                auto idx = convertCoord(x, y);
                if (prev_buffer[idx] != curr_buffer[idx]) {
                    std::vector<TextPixel> pixel;
                    pixel_changes.push_back(
                        TextPixel(x, y, curr_buffer[idx]));
                }
            }
        }

        return pixel_changes;
    }
}