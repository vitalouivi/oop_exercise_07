#include <array>
#include <memory>
#include <vector>
#include <stack>

#include "sdl.h"
#include "imgui.h"

#include "quadrangle.h"
#include "curve_line.h"
#include "circle.h"
#include "polygon.h"

#include "color.h"
#include "Document.h"

int main() {
	sdl::renderer renderer("Editor");
	bool quit = false;

	std::unique_ptr<builder> active_builder = nullptr;
	bool active_deleter = false;
	const int32_t file_name_length = 128;
	char file_name[file_name_length] = "";
	int32_t remove_id = 0;
	std::vector<int> color(3);

	Document currentDocument;

	while (!quit) {
		renderer.set_color(0, 0, 0);
		renderer.clear();

		sdl::event event;

		while (sdl::event::poll(event)) {
			sdl::quit_event quit_event;
			sdl::mouse_button_event mouse_button_event;
			if (event.extract(quit_event)) {
				quit = true;
				break;
			} else if (event.extract(mouse_button_event)) {
				if (active_builder && mouse_button_event.button() == sdl::mouse_button_event::left && mouse_button_event.type() == sdl::mouse_button_event::down) {
					std::unique_ptr<figure> figure = active_builder->add_vertex(vertex{mouse_button_event.x(), mouse_button_event.y()});
					if (figure) {
						figure -> setColor(color);

						currentDocument.addFigure(std::move(figure));

						active_builder = nullptr;
					}
				}
				if (active_builder && mouse_button_event.button() == sdl::mouse_button_event::right && mouse_button_event.type() == sdl::mouse_button_event::down) {
					std::unique_ptr<figure> figure = active_builder->add_vertex(vertex{-1, -1});
					if (figure) {
						figure -> setColor(color);
						
						currentDocument.addFigure(std::move(figure));

						active_builder = nullptr;
					}
				}
				if (active_deleter && mouse_button_event.button() == sdl::mouse_button_event::left && mouse_button_event.type() == sdl::mouse_button_event::down) {
					
					currentDocument.removeByClick(vertex{mouse_button_event.x(), mouse_button_event.y()});

					active_deleter = false;
				}
			}
		}

		currentDocument.render(renderer); 

		

		
		ImGui::Begin("Menu");
		if (ImGui::Button("New canvas")) {
			currentDocument.clear();
		}

		ImGui::InputText("File name", file_name, file_name_length - 1);

		if (ImGui::Button("Save")) {
			std::ofstream os(file_name);

			if (os) {
				currentDocument.Save(os);
			}

		}

		ImGui::SameLine();

		if (ImGui::Button("Load")) {
			std::ifstream is(file_name);

			if (is) {
				currentDocument.Load(is);
			}
				
		}


		ImGui::InputInt("R", &color[0]);
		ImGui::InputInt("G", &color[1]);
		ImGui::InputInt("B", &color[2]);
		if (ImGui::Button("Red")) {
			color[0] = 255;
			color[1] = 0;
			color[2] = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Green")) {
			color[0] = 0;
			color[1] = 255;
			color[2] = 0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Blue")) {
			color[0] = 0;
			color[1] = 0;
			color[2] = 255;
		}

		if (ImGui::Button("Quadrangle")) {
			active_builder = std::make_unique<quadrangle_builder>();
		}
		if (ImGui::Button("Broken Line")) {
			active_builder = std::make_unique<curve_line_builder>();
		}
		if (ImGui::Button("Circle")) {
			active_builder = std::make_unique<circle_builder>();
		}
		if (ImGui::Button("Polygon")) {
			active_builder = std::make_unique<polygon_builder>();
		}

		ImGui::InputInt("Remove id", &remove_id);
		if (ImGui::Button("Remove")) {
			if (remove_id >= 0 && remove_id < (currentDocument.figures).size()) {

				currentDocument.removeFigure(remove_id);

			}
		}
		if (ImGui::Button("Remove by click")) {
			active_deleter = true;
		}
		if (ImGui::Button("UNDO")) {

			currentDocument.undo();
		}

		ImGui::End();

		renderer.present();
	}


}