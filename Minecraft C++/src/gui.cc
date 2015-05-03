#include "../include/gui.h"

Gui::Gui(){

}


void Gui::init(){

}

void Gui::show(){
  //createDebugHeader();

  ImGui::End();
  ImGui::Render();
}

void Gui::createDebugHeader(){
  if (ImGui::CollapsingHeader("Debug")){
    //ImGui::Text("ASDAS");
  }
  
  
}
