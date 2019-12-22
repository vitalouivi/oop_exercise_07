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

struct  circle : figure {
    circle(const std::vector<vertex>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer) const override {
        int32_t centreX = vertices_[0].x;
        int32_t centreY = vertices_[0].y;
        const int32_t diameter = (radius * 2);

        int32_t x = (radius - 1);
        int32_t y = 0;
        int32_t tx = 1;
        int32_t ty = 1;
        int32_t error = (tx - diameter);

        renderer.set_color(color_.r, color_.g, color_.b);
        while (x >= y)
        {
            //  Each of the following renders an octant of the circle
            renderer.draw_point(centreX + x, centreY - y);
            renderer.draw_point(centreX + x, centreY + y);
            renderer.draw_point(centreX - x, centreY - y);
            renderer.draw_point(centreX - x, centreY + y);
            renderer.draw_point(centreX + y, centreY - x);
            renderer.draw_point(centreX + y, centreY + x);
            renderer.draw_point(centreX - y, centreY - x);
            renderer.draw_point(centreX - y, centreY + x);

            if (error <= 0)
            {
                ++y;
                error += ty;
                ty += 2;
            }

            if (error > 0)
            {
                --x;
                tx += 2;
                error += (tx - diameter);
            }
        }
       
    }

    void save(std::ostream& os) const override {
        os << "circle\n";
        os << vertices_[0].x << ' ' << vertices_[0].y << '\n';
        os << vertices_[1].x << ' ' << vertices_[1].y << '\n';
        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }

private:
    std::vector<vertex> vertices_;
    int radius = (int)sqrt((vertices_[1].y - vertices_[0].y) * (vertices_[1].y - vertices_[0].y) + (vertices_[1].x - vertices_[0].x) * (vertices_[1].x - vertices_[0].x));
};


struct circle_builder : builder {

	std::unique_ptr<figure> add_vertex(const vertex& v) override {
		vertices_.push_back(v);
		n_ += 1;
		if (n_ != 2) {
			return nullptr;
		}
		return std::make_unique<circle>(vertices_);

	}
private:
    int32_t n_ = 0;
    std::vector<vertex> vertices_;
};