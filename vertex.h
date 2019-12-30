
#ifndef D_VERTEX_H
#define D_VERTEX_H 1

#include <memory>
#include <fstream>
#include <iostream>

struct vertex {
	int32_t x, y;

};

inline std::istream& operator>> (std::istream& is, vertex& p) {
	is >> p.x >> p.y;
	return is;
}

#endif // !D_VERTEX_H
