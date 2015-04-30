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
  camera_position_[0] = 0;
  camera_position_[1] = 0;
  camera_position_[2] = 200;
  float view[] = { 0, 0, 200 };
  game_state_.camera->set_position(camera_position_);
  game_state_.camera->set_clear_color(0.135f, 0.206f, 0.235f, 1.0f);
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
  camera_front_.y = -sin(degreesToRadians(camera_pitch_));
  camera_front_.z= sin(degreesToRadians(camera_yaw_)) * cos(degreesToRadians(camera_pitch_));
  
  camera_front_ = camera_front_.normalize();
  
  float camera_view_[] = { camera_front_.x, camera_front_.y, camera_front_.z };

  //printf("%f %f %f\n", camera_front_.x, camera_front_.y, camera_front_.z);

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

  
  
  game_state_.camera->set_position(camera_position_);
  game_state_.camera->set_view_direction(camera_view_);
}


double GameManager::degreesToRadians(double deg) {
  return deg * M_PI / 180;
}
double GameManager::radiansToDegrees(double rad) {
  return rad * 180 / M_PI;
}
