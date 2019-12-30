#ifndef D_CURVE_LINE_H
#define D_CURVE_LINE_H 1

#include "figure.h"
#include "builder.h"


struct curve_line : figure {

	curve_line(const std::vector<vertex>& vertices);

	void setColor(std::vector<int> color) override;
	
	void render(const sdl::renderer& renderer) const override;
	void save(std::ostream& os) const override;


	bool isPointInside(vertex v) const override;

private:
	std::vector<int> color_;
	std::vector<vertex> vertices_;


};

struct curve_line_builder : builder {
	std::unique_ptr<figure> add_vertex(const vertex& v) override;

	std::string getType();
private:
	
	std::vector<vertex> vertices_;

};

#endif