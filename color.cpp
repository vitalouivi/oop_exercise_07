#include "color.h"


    color::color() : r(255), g(0), b(0) {}
    
    color::color(int r_, int g_, int b_) :r(r_), g(g_), b(b_) {}
    void color::set_color(int r_, int g_, int b_) { r = r_, g = g_, b = b_; }
