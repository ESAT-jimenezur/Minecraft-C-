/* Default Game Manager class implementation
*
* Jose Luis
*/

#include <iostream>

#include "../include/game_manager.h"
#include "../include/imaterial.h"
//#include "../include/chunk.h"
#include "../include/ichunk.h"
#include <stdio.h>



GameManager* GameManager::Instance() {
  static GameManager instance;
  return &instance;
}

GameManager::GameManager() {
  
  // Delete all of this
  
  // Create a cube
  //EDK3::ref_ptr<EDK3::Geometry> geo;
  //EDK3::CreateCube(&geo, 40, true, true);

  //EDK3::ref_ptr<iMaterial> mat;
  //EDK3::ref_ptr<iMaterial::Settings> mat_settings;

  //mat.alloc();
  //mat_settings.alloc();
  //float color[] = { 0.0, 0.0, 0.0, 1.0 };
  //mat_settings->set_color(color);


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


  
}

GameState GameManager::game_state(){
  //GameManager::Instance()->game_state().root->addChild();
  return game_state_;
}

void GameManager::prepare(){
  EDK3::dev::GPUManager::CheckGLError("Prepare Start");

  // Adding root
  game_state_.root.alloc();

  // Setup camera
  game_state_.camera.alloc();
  camera_position_[0] = 0;
  camera_position_[1] = 0;
  camera_position_[2] = -20;
  float view[] = { 0, 0, -100 };
  game_state_.camera->set_position(camera_position_);
  //game_state_.camera->set_clear_color(0.135f, 0.206f, 0.235f, 1.0f);
  game_state_.camera->set_clear_color(255.0f, 255.0f, 255.0f, 255.0f);
  game_state_.camera->set_view_direction(view);
  game_state_.camera->setupPerspective(70, 8.0 / 6.0, 1.0f, 1500.0f);


  // Map setup
  EDK3::ref_ptr<iChunk> map;
  map.alloc();
  map->setupNoise(7.0f, 1.5f, 0.0005f);
  map->mapSize(150, 30, 150);
  map->setupMesh();

  // Material
  /*
  EDK3::ref_ptr<iMaterial> mat;
  EDK3::ref_ptr<iMaterial::Settings> mat_settings;

  mat.alloc();
  mat_settings.alloc();
  float color[] = { 255.0, 0.0, 0.0, 1.0 };
  mat_settings->set_color(color);

  EDK3::ref_ptr<EDK3::Drawable> drawable;
  mat_settings.alloc();
  mat_settings->set_color(color);
  drawable.alloc();
  drawable->set_geometry(map.get());
  drawable->set_material(mat.get());
  drawable->set_material_settings(mat_settings.get());
  drawable->set_position(0, 0, 0);
  drawable->set_HPR(0.0f, 0.0f, 0.0f);
  game_state_.root->addChild(drawable.get());
  */
  
  EDK3::ref_ptr<iMaterial> mat;
  EDK3::ref_ptr<iMaterial::Settings> mat_settings;
  mat.alloc();
  mat_settings.alloc();
  

  EDK3::ref_ptr<EDK3::Texture> grass_texture;
  EDK3::Texture::Load("grass.png", &grass_texture);
  if (!grass_texture) {
    std::cerr << "¡No se puede cargar la textura!" << std::endl;
    exit(-2);
  }
  mat_settings->set_texture(grass_texture.get());


  EDK3::ref_ptr<EDK3::Drawable> drawable;

  drawable.alloc();
  drawable->set_name("map");
  drawable->set_geometry(map.get());
  drawable->set_material(mat.get());
  drawable->set_material_settings(mat_settings.get());
  drawable->set_position(0, -50, -50);
  drawable->set_HPR(0, 0, 0);
  game_state_.root->addChild(drawable.get());
  
  
  EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void GameManager::render(){
  game_state_.camera->doCull(game_state_.root.get());
  EDK3::dev::GPUManager::CheckGLError("begin Render-->");
  game_state_.camera->doRender();
  EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

void GameManager::loop(){
  mouseInput();
  render();
}

void GameManager::mouseInput(){

  double mx = ESAT::MousePositionX();
  double my = ESAT::MousePositionY();

  if (first_mouse_){
    camera_last_x_ = mx;
    camera_last_y_ = my;
    first_mouse_ = false;
  }

  float camera_offset_x_ = mx - camera_last_x_;
  float camera_offset_y_ = my - camera_last_y_;

  
  camera_last_x_ = mx;
  camera_last_y_ = my;

  camera_offset_x_ *= camera_sensivity_;
  camera_offset_y_ *= camera_sensivity_;

  camera_yaw_ += camera_offset_x_;
  camera_pitch_ += camera_offset_y_;
  
  /*
  if (camera_pitch_ > 89.0f){
    camera_pitch_ = 89.0f;
  }
  if (camera_pitch_ < -89.0f){
    camera_pitch_ = -89.0f;
  }*/
  

  Vector3 camera_front_;
  camera_front_.x = cos(degreesToRadians(camera_yaw_)) * cos(degreesToRadians(camera_pitch_));
  camera_front_.y = sin(degreesToRadians(camera_pitch_));
  camera_front_.z= sin(degreesToRadians(camera_yaw_)) * cos(degreesToRadians(camera_pitch_));
  
  camera_front_ = camera_front_.normalize();
  
  float camera_view_[] = { camera_front_.x, camera_front_.y, camera_front_.z };

  float n_camera_pos_[3];
  if (ESAT::IsKeyDown('W')){
    n_camera_pos_[0] = camera_view_[0] * movement_speed_;
    n_camera_pos_[1] = camera_view_[1] * movement_speed_;
    n_camera_pos_[2] = camera_view_[2] * movement_speed_;

    camera_position_[0] = camera_position_[0] + n_camera_pos_[0];
    camera_position_[1] = camera_position_[1] + n_camera_pos_[1];
    camera_position_[2] = camera_position_[2] + n_camera_pos_[2];
  }
  else if(ESAT::IsKeyDown('S')){
    n_camera_pos_[0] = camera_view_[0] * movement_speed_;
    n_camera_pos_[1] = camera_view_[1] * movement_speed_;
    n_camera_pos_[2] = camera_view_[2] * movement_speed_;

    camera_position_[0] = camera_position_[0] - n_camera_pos_[0];
    camera_position_[1] = camera_position_[1] - n_camera_pos_[1];
    camera_position_[2] = camera_position_[2] - n_camera_pos_[2];
  }

  //Debug Camera Pos
  if (ESAT::IsKeyDown('P')){
    if (debug_){
      debug_ = false;
    }else{
      debug_ = true;
    }
  }

  if (debug_){
    if (ESAT::IsKeyDown('C')){ // Center Camera
      camera_view_[0] = 0;
      camera_view_[1] = 0;
      camera_view_[2] = 0;
    }
    //printf("%f - %f - %f\n", camera_position_[0], camera_position_[1], camera_position_[2]);
    printf("%f - %f - %f\n", camera_view_[0], camera_view_[1], camera_view_[2]);
  }
  
  game_state_.camera->set_position(camera_position_);
  game_state_.camera->set_view_direction(camera_view_);
}

void GameManager::loadLuaData(){
  lua_State* L = luaL_newstate();
  luaL_dofile(L, "settings/test.lua");
  luaL_openlibs(L);
  lua_pcall(L, 0, 0, 0);
  LuaRef s = getGlobal(L, "testString");
  LuaRef n = getGlobal(L, "number");
  std::string luaString = s.cast<std::string>();
  int answer = n.cast<int>();
  std::cout << luaString << std::endl;
  std::cout << "And here's our number:" << answer << std::endl;
}


double GameManager::degreesToRadians(double deg) {
  return deg * M_PI / 180;
}
double GameManager::radiansToDegrees(double rad) {
  return rad * 180 / M_PI;
}

float GameManager::getCameraPosX(){
  return camera_position_[0];
}
float GameManager::getCameraPosY(){
  return camera_position_[1];
}
float GameManager::getCameraPosZ(){
  return camera_position_[2];
}