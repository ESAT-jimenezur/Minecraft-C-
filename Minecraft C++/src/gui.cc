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
    if (ImGui::CollapsingHeader("Camera")){

      ImGui::Columns(2, "camera_columns");
      ImGui::Separator();
      ImGui::Text("Position"); ImGui::NextColumn();
      ImGui::Text("View"); ImGui::NextColumn();
      ImGui::Separator();

      ImGui::Text("X: %f", GameManager::Instance()->getCameraPosX());
      ImGui::Text("Y: %f", GameManager::Instance()->getCameraPosY());
      ImGui::Text("Z: %f", GameManager::Instance()->getCameraPosZ()); ImGui::NextColumn();

      ImGui::Text("X: %f", GameManager::Instance()->getCameraViewX());
      ImGui::Text("Y: %f", GameManager::Instance()->getCameraViewY());
      ImGui::Text("Z: %f", GameManager::Instance()->getCameraViewZ()); ImGui::NextColumn();

      ImGui::Columns(1);

      ImGui::Separator();
      ImGui::Spacing();

      /*
      if (ImGui::CollapsingHeader("Position")){
        ImGui::Text("X: %f", GameManager::Instance()->getCameraPosX());
        ImGui::Text("Y: %f", GameManager::Instance()->getCameraPosY());
        ImGui::Text("Z: %f", GameManager::Instance()->getCameraPosZ());
      }
      if (ImGui::CollapsingHeader("View")){
        ImGui::Text("X: %f", GameManager::Instance()->getCameraViewX());
        ImGui::Text("Y: %f", GameManager::Instance()->getCameraViewY());
        ImGui::Text("Z: %f", GameManager::Instance()->getCameraViewZ());
      }
      */
    }

  }


}

void Gui::getSceneObjects(){

}