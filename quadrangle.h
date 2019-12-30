#ifndef D_QUADRANGLE_H
#define D_QUADRANGLE_H 1

#include "figure.h"
#include "builder.h"

struct quadrangle : figure {
    quadrangle(const std::array<vertex, 4>& vertices) ;
    void setColor(std::vector<int> color);

    void render(const sdl::renderer& renderer) const override;

    void save(std::ostream& os) const override;
    bool isPointInside(vertex v) const override;

private:
    std::array<vertex, 4> vertices_;
    std::vector<int> color_;

};

struct quadrangle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v);
    std::string quadrangle_builder::getType();

private:
    int32_t n_ = 0;
    std::array<vertex, 4> vertices_;

};

#endif