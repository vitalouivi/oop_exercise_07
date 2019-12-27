#ifndef POLYGON_H
#define POLYGON_H 1

#include "figure.h"
#include "builder.h"

struct  polygon : figure {
    polygon(const std::vector<vertex>& vertices);

    void render(const sdl::renderer& renderer) const override;

    void save(std::ostream& os) const override;

private:
    std::vector<vertex> vertices_;

};

struct  polygon_builder : builder {
    std::unique_ptr<figure> add_vertex(const vertex& v) override;


private:
    int32_t n_ = 0; 
    std::vector<vertex> vertices_;
};
#endif