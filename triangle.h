#pragma once

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include "windows.h"
#include <conio.h>
#include <stack>
#include "figure.h"


struct triangle : figure {
    triangle(const std::array<vertex, 3>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < 3; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1) % 3].x, vertices_[(i + 1) % 3].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "triangle" << std::endl;;
        for (int32_t i = 0; i < 3; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }

private:
    std::array<vertex, 3> vertices_;

};

struct triangle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 3) {
            return nullptr;
        }
        return std::make_unique<triangle>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::array<vertex, 3> vertices_;

};