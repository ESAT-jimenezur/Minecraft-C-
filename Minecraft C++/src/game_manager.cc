/* Default Game Manager class implementation
*
* Jose Luis
*/

#include "../include/game_manager.h"

#include <stdio.h>



GameManager* GameManager::Instance() {
  static GameManager instance;
  return &instance;
}

GameManager::GameManager() {
  EDK3::dev::GPUManager::CheckGLError("Prepare Start");
  
  // Create a cube
  //EDK3::ref_ptr<EDK3::Geometry> geo;
  //EDK3::CreateCube(&geo, 40, true, true);

  //EDK3::ref_ptr<iMaterial> mat;
  //EDK3::ref_ptr<iMaterial::Settings> mat_settings;

  //mat.alloc();
  //mat_settings.alloc();
  //float color[] = { 0.0, 0.0, 0.0, 1.0 };
  //mat_settings->set_color(color);


  // Adding root
  game_state_.root.alloc();


  // Create a Drawable Node (Geometry+Material+Settings)
  //EDK3::ref_ptr<EDK3::Drawable> drawable;
  //mat_settings.alloc();
  //mat_settings->set_color(color);
  //drawable.alloc();
  //drawable->set_geometry(geo.get());
  //drawable->set_material(mat.get());
  //drawable->set_material_settings(mat_settings.get());
  //drawable->set_position(0.0f, 0.0f, -20.0f);
  //drawable->set_HPR(0.0f, 0.0f, 0.0f);
  //game_state_.root->addChild(drawable.get());



  // Setup camera
  game_state_.camera.alloc();
  float pos[] = { 20, 40, -25 };
  float view[] = { 0, 0, -120 };
  game_state_.camera->set_position(pos);
  game_state_.camera->set_clear_color(88.0f, 88.0f, 88.0f, 1.0f);
  game_state_.camera->set_view_direction(view);
  game_state_.camera->setupPerspective(70, 8.0 / 6.0, 1.0f, 1500.0f);

  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

GameState GameManager::game_state(){
  //GameManager::Instance()->game_state().root->addChild();
  return game_state_;
}

void GameManager::render(){
  game_state_.camera->doCull(game_state_.root.get());
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  game_state_.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void GameManager::loop(){
  double mx = ESAT::MousePositionX();
  double my = ESAT::MousePositionY();
  double p = sin(-my / 200) * 220;
  float pos[] = { p*cos(mx / 100), cos(-my / 200) * 220, p*sin(mx / 100) };
  float view[] = { -pos[0], -pos[1], -pos[2] };
  //game_state_.camera->set_position(pos);
  game_state_.camera->set_view_direction(view);


  render();
}
