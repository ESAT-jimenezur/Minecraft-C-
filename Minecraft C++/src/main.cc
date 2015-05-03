#include <iostream>
#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include "../include/simplexnoise.h"

#include "../include/game_manager.h"
#include "../include/chunk.h"
#include "../include/gui.h"






int ESAT::main(int argc, char **argv) {

  ESAT::WindowInit(1024, 768);
  GameManager* game_manager = GameManager::Instance();
  game_manager->loadLuaData();
  game_manager->prepare();

  Gui gui;

  while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    //ESAT::DrawBegin();


    game_manager->loop();
    gui.show();

    //ESAT::DrawEnd();
    ESAT::WindowFrame();
  }

  return 0;
}