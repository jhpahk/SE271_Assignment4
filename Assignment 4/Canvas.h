#pragma once
////////////////////////////////////////////////////////////////////////////////
// SE271 - Assignment 4: Snake Arena
// Note: You will not submit this file
////////////////////////////////////////////////////////////////////////////////

namespace snake_arena {
    // Interface class to draw frames to somewhere
    class Canvas {
    public:
        virtual ~Canvas() {};
        virtual bool addLine(const char* line) = 0;
        virtual void draw() = 0;
    };
}
