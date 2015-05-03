#include "../include/gui.h"

Gui::Gui(){

}


void Gui::init(){

}

void Gui::show(){
  ImGui::Begin("Minecraft C++");

  createDebugHeader();
  getSceneObjects();

  ImGui::End();
  ImGui::Render();
}

void Gui::createDebugHeader(){
  if (ImGui::CollapsingHeader("Debug Info")){
    if (ImGui::CollapsingHeader("Camera Position")){
      ImGui::Text("X: %f", GameManager::Instance()->getCameraPosX());
      ImGui::Text("Y: %f", GameManager::Instance()->getCameraPosY());
      ImGui::Text("Z: %f", GameManager::Instance()->getCameraPosZ());
    }
  }


}

void Gui::getSceneObjects(){

}