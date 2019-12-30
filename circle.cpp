#include "circle.h"

circle::circle(const std::vector<vertex>& vertices) : vertices_(vertices) {
	radius = (int) sqrt((vertices_[1].y - vertices_[0].y) * (vertices_[1].y - vertices_[0].y) + (vertices_[1].x - vertices_[0].x) * (vertices_[1].x - vertices_[0].x));
}

void circle::setColor(std::vector<int> color) {
	for (int i = 0; i < 3; i++) {
		color_.push_back(color[i]);
	}
}

void circle::render(const sdl::renderer& renderer) const {
	renderer.set_color(color_[0], color_[1], color_[2]);

		

		/*

		*_______*
				|
			  	*

		*/

	int32_t centreX = vertices_[0].x;
	int32_t centreY = vertices_[0].y;
		
	const int32_t diameter = (radius * 2);

   	int32_t x = (radius - 1);                                         
   	int32_t y = 0;
   	int32_t tx = 1;
   	int32_t ty = 1;
   	int32_t error = (tx - diameter);

   	while (x >= y)
   	{
      		//  Each of the following renders an octant of the circle
      	renderer.draw_point(centreX + x, centreY - y);
      	renderer.draw_point(centreX + x, centreY + y);
      	renderer.draw_point(centreX - x, centreY - y);
      	renderer.draw_point(centreX - x, centreY + y);
      	renderer.draw_point(centreX + y, centreY - x);
      	renderer.draw_point(centreX + y, centreY + x);
      	renderer.draw_point(centreX - y, centreY - x);
      	renderer.draw_point(centreX - y, centreY + x);

      	if (error <= 0)
      	{
         	++y;
         	error += ty;
         	ty += 2;
      	}
      	
      	if (error > 0)
      	{
         	--x;
         	tx += 2;
         	error += (tx - diameter);
      	}
   	}
}

void circle::save(std::ostream& os) const {
	os << "circle\n";
		
	os << vertices_[0].x << ' ' << vertices_[0].y << '\n';
	os << vertices_[1].x << ' ' << vertices_[1].y << '\n';
		
	os << color_[0] << ' ' << color_[1] << ' ' << color_[2] << '\n';
}


	/*          *
               /
	          /*
			 /_|
		  	  

	*/

bool circle::isPointInside(vertex v) const {
	int distance = (int) sqrt((v.y - vertices_[0].y) * (v.y - vertices_[0].y) + (v.x - vertices_[0].x) * (v.x - vertices_[0].x));
	if (distance <= radius) 
		return true;
	return false;
}


std::unique_ptr<figure> circle_builder::add_vertex(const vertex& v) {
	vertices_.push_back(v);
	n_ += 1;
	if (n_ != 2) {
		return nullptr;
	}
	return std::make_unique<circle>(vertices_);
}

std::string circle_builder::getType() {
	return "circle";
}
