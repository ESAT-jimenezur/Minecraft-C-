/** @brief Default Game Manager class declaration
*
* @author Jose Luis Jimenez Urbano | < ijos@ijos.es > | < @iJos >
*/

#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__


#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <ESAT/input.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/texture.h>
#include <EDK3/dev/gpumanager.h>

#include "../include/imaterial.h"

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

  void render();
  void loop();

private:
  static GameManager *instance;
  GameManager::GameManager();


  GameState game_state_;
  
};

#endif __GAME_MANAGER_H__