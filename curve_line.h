#ifndef CURVELINE_H
#define CURVELINE_H 1

#include "figure.h"
#include "builder.h"


struct curve_line : figure {
    curve_line(const std::vector<vertex>& vertices);

    void render(const sdl::renderer& renderer) const override;

    void save(std::ostream& os) const override;

private:
    std::vector<vertex> vertices_;
};

struct curve_line_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) override;

private:
    int32_t n_ = 0;
    std::vector<vertex> vertices_;

};

#endif
