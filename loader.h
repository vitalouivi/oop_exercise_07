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

struct loader {

    std::vector<std::unique_ptr<figure>> load(std::ifstream& is) {
        std::string figure_name;
        std::vector<std::unique_ptr<figure>> figures;
        while (is >> figure_name) {
            vertex v;
            if (figure_name == std::string("trapezoid")) {
                std::array<vertex, 4> vertices;
                for (int i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<trapezoid>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);

            }
            else if (figure_name == std::string("rectangle")) {
                std::array<vertex, 4> vertices;
                for (int i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<rectangle>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }
            else if (figure_name == std::string("rhombus")) {
                std::array<vertex, 4> vertices;
                for (int i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<rhombus>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }
            else if (figure_name == std::string("curve_line")) {
                std::vector<vertex> vertices;
                int count_v;
                is >> count_v;
                for (int i = 0; i < count_v; ++i) {
                    is >> v.x >> v.y;
                    vertices.push_back(v);
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<curve_line>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }

            else if (figure_name == std::string("square")) {
                std::array<vertex, 4> vertices;
                for (int i = 0; i < 4; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<square>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }
            else if (figure_name == std::string("circle")) {
                std::vector<vertex> vertices(2);
                is >> vertices[0] >> vertices[1];
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<circle>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }
            else if (figure_name == std::string("triangle")) {
                std::array<vertex, 3> vertices;
                for (int i = 0; i < 3; ++i) {
                    is >> v.x >> v.y;
                    vertices[i] = v;
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<triangle>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }
            else if (figure_name == std::string("polygon")) {
                std::vector<vertex> vertices;
                int count_v;
                is >> count_v;
                for (int i = 0; i < count_v; ++i) {
                    is >> v.x >> v.y;
                    vertices.push_back(v);
                }
                struct color buffcolor {};
                is >> buffcolor.r >> buffcolor.g >> buffcolor.b;

                figures.emplace_back(std::make_unique<curve_line>(vertices));
                (*figures[figures.size() - 1]).set_color(buffcolor);
            }
        }
        return figures;
    }
    ~loader() = default;
};