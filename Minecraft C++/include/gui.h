#ifndef __GUI_H__
#define __GUI_H__

#include <EDK3\imgui.h>
#include "game_manager.h"

class Gui{

public:

  Gui();
  ~Gui(){};

  void init();
  void show();

private:

  void getSceneObjects();
  void createDebugHeader();

};

#endif //__GUI_H__