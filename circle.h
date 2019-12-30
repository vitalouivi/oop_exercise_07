#ifndef D_CIRCLE_H
#define D_CIRCLE_H 1

#include "figure.h"
#include "builder.h"
#include <math.h>

struct circle : figure {
	circle(const std::vector<vertex>& vertices);

	void setColor(std::vector<int> color) override;

	void render(const sdl::renderer& renderer) const override;

	void save(std::ostream& os) const override;

	bool isPointInside(vertex v) const override;

private:
	std::vector<int> color_;
	std::vector<vertex> vertices_;
	int radius;
};

struct circle_builder : builder {

	std::unique_ptr<figure> add_vertex(const vertex& v) override;

	std::string getType() override;

private:

	int32_t n_ = 0;
	
	std::vector<vertex> vertices_;

};


#endif