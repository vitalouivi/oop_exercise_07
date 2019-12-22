struct Bline : figure {
    Bline(const std::array<vertex, 10>& vertices) : vertices_(vertices) {}

    void render(const sdl::renderer& renderer, int cx, int cy, int cz) const override {
        renderer.set_color(cx, cy, cz);
        for (int32_t i = 0; i < 9; ++i) {
            renderer.draw_line(vertices_[i].x, vertices_[i].y,
                vertices_[(i + 1) % 10].x, vertices_[(i + 1) % 10].y);
        }
    }

    void save(std::ostream& os) const override {
        os << "Bline";
        for (int32_t i = 0; i < 10; ++i) {
            os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
        }
    }

private:
    std::array<vertex, 10> vertices_;

};

struct Bline_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) {
        vertices_[n_] = v;
        n_ += 1;
        if (n_ != 10) {
            return nullptr;
        }
        return std::make_unique<Bline>(vertices_);
    }

private:
    int32_t n_ = 0;
    std::array<vertex, 10> vertices_;

};