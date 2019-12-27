#include"triangle.h"

triangle::triangle(const std::array<vertex, 3>& vertices) : vertices_(vertices) {}

    void triangle::render(const sdl::renderer& renderer) const {
        renderer.set_color(color_.r, color_.g, color_.b);
        for (int32_t i = 0; i < 3; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1) % 3].x, vertices_[(i + 1) % 3].y);
        }
    }

    void triangle::save(std::ostream& os) const  {
        os << "triangle" << std::endl;;
        for (int32_t i = 0; i < 3; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
        os << this->color_.r << ' ' << this->color_.g << ' ' << this->color_.b << std::endl;
    }




    std::unique_ptr<figure> triangle_builder::add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 3) {
            return nullptr;
        }
        return std::make_unique<triangle>(vertices_);
    }
triangle:~builder() = default;