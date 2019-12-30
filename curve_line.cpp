#include "curve_line.h"

curve_line::curve_line(const std::vector<vertex>& vertices) : vertices_(vertices) {}

void curve_line::setColor(std::vector<int> color) {
	for (int i = 0; i < 3; i++) {
		color_.push_back(color[i]);
	}
}
	
void curve_line::render(const sdl::renderer& renderer) const {
	renderer.set_color(color_[0], color_[1], color_[2]);
	for (int32_t i = 0; i < vertices_.size() - 1; ++i) {
		renderer.draw_line(vertices_[i].x, vertices_[i].y, 
			vertices_[(i + 1)].x, vertices_[(i + 1)].y);
	}
}

void curve_line::save(std::ostream& os) const {
	os << "curve line\n";
	os << vertices_.size() << '\n';
	for (int32_t i = 0; i < vertices_.size(); ++i) {
		os << vertices_[i].x << ' ' << vertices_[i].y << '\n';
	}
	os << color_[0] << ' ' << color_[1] << ' ' << color_[2] << '\n';
}


bool curve_line::isPointInside(vertex v) const {
	return false;
}

std::unique_ptr<figure> curve_line_builder::add_vertex(const vertex& v) {
	if (v.x != -1 && v.y != -1) {
		vertices_.push_back(v);
		return nullptr;
	}
		
	return std::make_unique<curve_line>(vertices_);
}

std::string curve_line_builder::getType() {
	return "curve line";
}
