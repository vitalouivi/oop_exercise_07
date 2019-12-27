#ifndef CIRCLE_H
#define CIRCLE_H 1

#include "figure.h"
#include "builder.h"


struct circle : figure {
    circle(const std::vector<vertex>& vertices);

    void render(const sdl::renderer& renderer) const override;

    void save(std::ostream& os) const override;

private:
    std::vector<vertex> vertices_;
    int radius = (int)sqrt((vertices_[1].y - vertices_[0].y) * (vertices_[1].y - vertices_[0].y) + (vertices_[1].x - vertices_[0].x) * (vertices_[1].x - vertices_[0].x));
};

struct circle_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) override;


private:
    int32_t n_ = 0;
    std::vector<vertex> vertices_;

};

#endif