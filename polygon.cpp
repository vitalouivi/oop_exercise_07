#include"polygon.h"


    polygon::polygon(const std::vector<vertex>& vertices) : vertices_(vertices) {}

    void polygon::render(const sdl::renderer& renderer) const override {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1)].x, vertices_[(i + 1)].y);
        }
        renderer.draw_line(vertices_[vertices_.size() - 1].x, vertices_[vertices_.size() - 1].y, vertices_[0].x, vertices_[0].y);
    }

    void polygon::save(std::ostream& os) const override {
        os << "polygon" << ' ' << vertices_.size() << std::endl;
        for (int32_t i = 0; i < vertices_.size(); ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }



    std::unique_ptr<figure> polygon_builder::add_vertex(const vertex& v) {
        if (v.x != -1 && v.y != -1) {
            vertices_.push_back(v);
            return nullptr;
        }

        return std::make_unique<polygon>(vertices_);
    }
    polygon_builder::~builder() = default;