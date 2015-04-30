/** @brief Default Game Manager class declaration
*
* @author Jose Luis Jimenez Urbano | < ijos@ijos.es > | < @iJos >
*/

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include <math.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <ESAT/input.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/texture.h>
#include <EDK3/dev/gpumanager.h>

#include "../include/imaterial.h"
#include "../include/vector3.h"

# define M_PI           3.14159265358979323846  /* pi */

struct GameState{
  EDK3::ref_ptr<EDK3::Camera> camera;
  EDK3::ref_ptr<EDK3::Node> root;
};

class GameManager{
public:

  const int kScreenWidth = 1024;
  const int kScreenHeight = 768;

  // Singleton instance
  static GameManager *Instance();

  // Getters
  GameState game_state();

  //Utils
  double degreesToRadians(double deg);
  double radiansToDegrees(double rad);

  void mouseInput();
  void render();
  void loop();

private:
  static GameManager *instance;
  GameManager::GameManager();

  const float camera_sensivity_ = 0.4f;
  const float movement_speed_ = 10.0f;

  bool first_mouse_ = true;

  float camera_last_x_;
  float camera_last_y_;

  float camera_offset_;
  float camera_pitch_;
  float camera_yaw_;

  float camera_position_[3];

  GameState game_state_;
  
};

#endif __GAME_MANAGER_H__