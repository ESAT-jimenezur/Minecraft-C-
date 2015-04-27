#include <iostream>
#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include "../include/simplexnoise.h"

#include "../include/game_manager.h"
#include "../include/chunk.h"



int ESAT::main(int argc, char **argv) {

  ESAT::WindowInit(1024, 768);
  GameManager* game_manager = GameManager::Instance();

  Chunk chunk;
  chunk.init(); // Clear array and make some things
  chunk.setupNoise(); // Fill our 3d map array with noise data
  chunk.createMesh(); // Parse 3d map array and draw faces
 

  while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    //ESAT::DrawBegin();


    game_manager->loop();
    

    //ESAT::DrawEnd();
    ESAT::WindowFrame();
  }

  return 0;
}