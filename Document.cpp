#include "Document.h"


void Document::addFigure(std::unique_ptr<figure> fig) {
	figures.emplace_back(std::move(fig));
	
	commandStack.push(std::make_unique<CommandAdd>(figures.size() - 1, this));

}
void Document::removeFigure(int id) {
	commandStack.push(std::make_unique<CommandRemove>(id, figures[id], this));
	figures.erase(figures.begin() + id);

}
void Document::undo() {
	if (commandStack.size()) {

		commandStack.top() -> undo();

		commandStack.pop();
	
	}
}

void Document::removeByClick(vertex v) {
	std::vector<int> toDelete;
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i] -> isPointInside(v)) {
			toDelete.push_back(i);
			commandStack.push(std::make_unique<CommandRemove>(i, figures[i], this));
		}
	}

	for (int i = 0; i < toDelete.size(); i++) {
		figures.erase(figures.begin() + toDelete[i] - i);
	}
}

void Document::render(const sdl::renderer& renderer) {
	for (const std::shared_ptr<figure>& figure : figures) {
		figure -> render(renderer);
	}
}

void Document::Save(std::ofstream& os) {
	for (const std::shared_ptr<figure>& figure : figures) {
		figure -> save(os);
	}
}

void Document::Load(std::ifstream& is) {

	figures.clear();

	while ( ! commandStack.empty() )
	{
    	commandStack.pop();
	}
	
	std::string type;

	while(std::getline(is, type)) {
		if (type == "quadrangle") {
			std::array<vertex, 4> vrt;
			for (int i = 0; i < 4; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> trap = std::make_unique<quadrangle>(vrt);
			trap -> setColor(colorTmp);
			figures.emplace_back(std::move(trap));
		} else if (type == "polygon") {
			int sz;
			is >> sz;
			std::vector<vertex> vrt(sz);
						
			for (int i = 0; i < sz; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> poly = std::make_unique<polygon>(vrt);
			poly -> setColor(colorTmp);
			figures.emplace_back(std::move(poly));
		} else if (type == "curve line") {
			int sz;
			is >> sz;
			std::vector<vertex> vrt(sz);
					
			for (int i = 0; i < sz; i++) {
				is >> vrt[i];
			}
			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}
			std::unique_ptr<figure> bl = std::make_unique<curve_line>(vrt);
			bl -> setColor(colorTmp);
			figures.emplace_back(std::move(bl));
		} else if (type == "circle") {
			std::vector<vertex> vrt(2);
			is >> vrt[0] >> vrt[1];

			std::vector<int> colorTmp(3);
			for (int i = 0; i < 3; i++) {
				is >> colorTmp[i];
			}

			std::unique_ptr<figure> crcl = std::make_unique<circle>(vrt);
			crcl -> setColor(colorTmp);
			figures.emplace_back(std::move(crcl));
		}
			
	}

}

void Document::clear() {

	while ( ! commandStack.empty() )
	{
    	commandStack.pop();
	}

	figures.clear();

}