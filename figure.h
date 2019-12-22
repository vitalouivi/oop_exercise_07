#ifndef FIGURE_H
#define FIGURE_H

#include "sdl.h"
#include<iostream>
#include "color.h"

struct figure {
    virtual void render(const sdl::renderer& renderer) const = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual ~figure() = default;
    color color_{};
    virtual void set_color(int r, int g, int b) {
        color_.r = r;
        color_.g = g;
        color_.b = b;
    }
    virtual void set_color(color c) {
        color_.r = c.r;
        color_.g = c.g;
        color_.b = c.b;
    }

};

struct vertex {
    int32_t x, y;

};

struct builder {
    virtual std::unique_ptr<figure> add_vertex(const vertex& v) = 0;

    virtual ~builder() = default;

};

std::ifstream& operator>> (std::ifstream& is, vertex& p) {
    is >> p.x >> p.y;
    return is;
}
#endif