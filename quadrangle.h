#ifndef QUADRANGLE_H
#define QUADRANGLE_H 1

#include "figure.h"
#include "builder.h"

struct quadrangle : figure {
    quadrangle(const std::array<vertex, 4>& vertices) ;

    void render(const sdl::renderer& renderer) const override;

    void save(std::ostream& os) const override;

private:
    std::array<vertex, 4> vertices_;

};

struct quadrangle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v);

private:
    int32_t n_ = 0;
    std::array<vertex, 4> vertices_;

};

#endif