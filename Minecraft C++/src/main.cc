#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>


int ESAT::main(int argc, char **argv) {
  ESAT::WindowInit(1024, 768);

  while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
    ESAT::DrawBegin();



    ESAT::DrawEnd();
    ESAT::WindowFrame();
  }

  return 0;
}