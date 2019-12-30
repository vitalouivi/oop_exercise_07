#pragma once

#ifndef D_DOCUMENT_H
#define D_DOCUMENT_H 1

#include <array>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <stack>

#include "sdl.h"
#include "imgui.h"

#include"quadrangle.h"
#include "curve_line.h"
#include "circle.h"
#include "polygon.h"

struct Command;
struct CommandAdd;
struct CommandRemove;
struct Document;


struct Document {
public:
	Document() = default;

	void addFigure(std::unique_ptr<figure> fig);
	void removeFigure(int id);
	void removeByClick(vertex v);
	void undo();
	void Save(std::ofstream& os);
	void Load(std::ifstream& is);
	void render(const sdl::renderer& renderer);
	void clear();

	std::vector<std::shared_ptr<figure>> figures;
	std::stack<std::unique_ptr<Command>> commandStack;
};



struct Command {

	virtual ~Command() = default;

	virtual void undo() = 0;

};

struct CommandAdd : Command {


	int index__;
	Document * doc__ = new Document();

	CommandAdd(int index, Document * doc) : index__(index), doc__(doc) {}

	void undo() {
		(doc__ -> figures).erase((doc__ -> figures).begin() + index__);
	}
	
};

struct CommandRemove : Command {

	Document * doc__;

	int index__;
	std::shared_ptr<figure> figure__ = nullptr;

	CommandRemove(int index, std::shared_ptr<figure> figure_, Document * doc) : index__(index), figure__(figure_), doc__(doc) {}

	void undo() {
		if (index__ > (doc__ -> figures).size() - 1) 
			(doc__ -> figures).push_back(std::move(figure__));
		else 
			(doc__ -> figures).insert((doc__ -> figures).begin() + index__, std::move(figure__));
	}
	
};

#endif