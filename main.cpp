#include <array>
#include <conio.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>
#include "windows.h"

//#include "canvas.h"
#include "triangle.h"
#include "figure.h"
#include "color.h"
#include "rectangle.h"
#include "square.h"
#include "rhombus.h"
#include "trapezoid.h"
#include "curve_line.h"
#include "polygon.h"
#include "circle.h"

#include "loader.h"

#include "sdl.h"
#include "imgui.h"



int main() {
    int x=0;
    int y = 0;
    color figure_color{};
//    canvas c;
   
  sdl::renderer renderer("Editor");
  bool quit = false;
  HWND sHwnd = ::FindWindow(NULL, "Editor");
  HDC hdc = GetDC(sHwnd);
  for (x; x < 600; x += 3);
  {
      for (y; y < 800; y += 3)
      {
          SetPixel(hdc, x, y, RGB(255, 0, 0));
      }
  }
  std::vector<std::unique_ptr<figure>> figures;
  std::unique_ptr<builder> active_builder = nullptr;
  const int32_t file_name_length = 128;
  char file_name[file_name_length] = "";
  int32_t remove_id = 0;
  while(!quit){
    renderer.set_color(0, 0, 0);
    renderer.clear();

    sdl::event event;

    while(sdl::event::poll(event)){
      sdl::quit_event quit_event;
      sdl::mouse_button_event mouse_button_event;
      if(event.extract(quit_event)){
        quit = true;
        break;
      }else if(event.extract(mouse_button_event)){
        if(active_builder && mouse_button_event.button() == sdl::mouse_button_event::left &&
            mouse_button_event.type() == sdl::mouse_button_event::down){
          std::unique_ptr<figure> figure =
            active_builder->add_vertex(vertex{mouse_button_event.x(), mouse_button_event.y()});
          if(figure){
              (*figure).set_color(figure_color);
            figures.emplace_back(std::move(figure));
            active_builder = nullptr;
          }
        }
      }
    }

    for(const std::unique_ptr<figure>& figure: figures){
        
      figure->render(renderer);
    }

    ImGui::Begin("Menu");
    if(ImGui::Button("New canvas")){
        figures.clear();
    }
    ImGui::InputInt("R", &figure_color.r);
    ImGui::InputInt("G", &figure_color.g);
    ImGui::InputInt("B", &figure_color.b);
    if (ImGui::Button("Red")) {
        figure_color.set_color(255, 0, 0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Green")) {
        figure_color.set_color(0, 255, 0);
    }
    ImGui::SameLine();
    if (ImGui::Button("Blue")) {
        figure_color.set_color(0, 0, 255);
    }
   
    ImGui::InputText("File name", file_name, file_name_length - 1);
    if(ImGui::Button("Save")){
      std::ofstream os(file_name);
      if(os){
        for(const std::unique_ptr<figure>& figure: figures){
          figure->save(os);
        }
      }
    }
    ImGui::SameLine();
    if(ImGui::Button("Load")){
      std::ifstream is(file_name);
      if(is){
         loader loader;
         figures = loader.load(is);
      }
    }
    if(ImGui::Button("Triangle")){
      active_builder = std::make_unique<triangle_builder>();
    }
    if (ImGui::Button("Rectangle")) {
        active_builder = std::make_unique<rectangle_builder>();
    }
    if (ImGui::Button("Square")) {
        active_builder = std::make_unique<square_builder>();
    }
    if (ImGui::Button("Rhombus")) {
        active_builder = std::make_unique<rhombus_builder>();
    }
    if (ImGui::Button("Trapezoid")) {
        active_builder = std::make_unique<trapezoid_builder>();
    }
    if (ImGui::Button("Curve Line")) {
        active_builder = std::make_unique<curve_line_builder>();
    }
	if (ImGui::Button("Polygon")) {
		active_builder = std::make_unique<polygon_builder>();
	}
    if (ImGui::Button("Circle")) {
        active_builder = std::make_unique<circle_builder>();
    }


    ImGui::InputInt("Remove id", &remove_id);
    if(ImGui::Button("Remove")){
     
      figures.erase(figures.begin() + remove_id);
    }
    if (ImGui::Button("Undo")) {

    }
    ImGui::End();

    renderer.present();
  }
}
