#pragma once 

#include<vector>
#include<stack>
#include<memory>
#include"figure.h"

struct command {
	//command() = default;
	virtual void undo() = 0;
	virtual ~command() = default;
};

struct add_command : command {
private:
	canvas* canvas_p;
public:
	//add_command() {}
	add_command(canvas* canvas_) {
		canvas_p = canvas_;
	}
	void undo() override {
		(*canvas_p).figures.pop_back();
	}
};


struct canvas {
	void canvas::add_figure(std::unique_ptr<figure> fig) {
		figures.emplace_back(std::move(fig));
		command_stack.push(std::make_unique<add_command>(add_command(this)));//?
	}
	void canvas::remove_figure(int id) {
		command_stack.push(std::make_unique<remove_command>(remove_command(this, std::move(figures[id]), id)));
		//figures.pop_back();
	}
	void canvas::undo() {
		if (command_stack.size()) {
			command_stack.top()->undo();
			command_stack.pop();
		}
	}
	void remove_command::undo() {
		(*canvas_p).figures[id] = std::move(fig);
	}
	remove_command::remove_command(canvas* canvas_, std::unique_ptr<figure> fig_, int id_) {
		canvas_p = canvas_;
		fig = std::move(fig_);
		id = id_;
	}
};