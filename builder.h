
#ifndef D_BUILDER_H
#define D_BUILDER_H 1

#include "figure.h"

struct builder {
	virtual std::unique_ptr<figure> add_vertex(const vertex& v) = 0;
	virtual std::string getType() = 0;

	virtual ~builder() = default;

};

#endif //!D_BUILDER_H