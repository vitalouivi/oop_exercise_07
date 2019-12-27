#ifndef TRIANGLE_H
#define TRIANGLE_H 1

#include "figure.h"
#include "builder.h"


struct triangle : figure {
    triangle(const std::array<vertex, 3>& vertices);

    void render(const sdl::renderer& renderer) const override;

    void save(std::ostream& os) const override;

private:
    std::array<vertex, 3> vertices_;
};

struct triangle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) override;

private:
    int32_t n_ = 0;
    std::array<vertex, 3> vertices_;

};

#endif