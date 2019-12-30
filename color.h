#ifndef D_COLOR_H 
#define D_COLOR_H 1

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>

struct color {
    color();
    int32_t r, g, b;
    color(int r_, int g_, int b_);
    void set_color(int r_, int g_, int b_);
};
#endif // !D_COLOR_H 

