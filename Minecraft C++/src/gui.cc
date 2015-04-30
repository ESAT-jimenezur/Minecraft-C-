#include "../include/gui.h"

Gui::Gui(){

}


void Gui::init(){

}

void Gui::show(){
  ImGui::Begin("Game Objects");

  createObjectsHeader();
  getSceneObjects();

  ImGui::End();
  ImGui::Render();
}

void Gui::createObjectsHeader(){
  if (ImGui::CollapsingHeader("Create Object")){
    ImGui::Button("Boton");
  }
  
  
}

void Gui::getSceneObjects(){
  
}