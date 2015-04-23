#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffusetexture.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/texture.h>
#include <EDK3/dev/gpumanager.h>

#include "game_manager.h"
#include "imaterial.h"
#include "cube.h"
#include "simplexnoise.h"

class Chunk{
public:
  Chunk();
  ~Chunk();

  void init();
  void update(float dt);
  void render();
  void setupNoise();
  void createMesh();
  void createCube(float x, float y, float z);

  

private:
  static const int CHUNK_WIDTH = 10;
  static const int CHUNK_HEIGHT = 10;
  static const int CHUNK_DEEP = 10;
  float noise;

  float map3d[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEEP];
};