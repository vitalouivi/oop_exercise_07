
#ifndef D_FIGURE_H
#define D_FIGURE_H 1

#include "vertex.h"

#include "sdl.h"
#include <array>
#include <vector>
#include <memory>
//#include <iostream>
//#include <fstream>
#include <string>


struct figure {
	virtual void render(const sdl::renderer& renderer) const = 0;
	virtual void save(std::ostream& os) const = 0;
	virtual bool isPointInside(vertex v) const = 0;
	virtual void setColor(std::vector<int> color) = 0;
	virtual ~figure() = default;

};

#endif // !D_FIGURE_H