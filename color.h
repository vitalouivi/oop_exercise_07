#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>

struct color {
    color() : r(255), g(0), b(0) {}
    int32_t r, g, b;
    color(int r_, int g_, int b_) :r(r_), g(g_), b(b_) {}
    void set_color(int r_, int g_, int b_) { r = r_, g = g_, b = b_; }
};