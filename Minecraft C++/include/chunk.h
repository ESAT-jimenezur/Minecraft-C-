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

  bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const;
  void render()const;

private:
  static const int CHUNK_WIDTH = 10;
  static const int CHUNK_HEIGHT = 1;
  static const int CHUNK_DEEP = 1;
  float noise;

  std::vector<float> chunk_vertex_;
  std::vector<float> chunk_normal_;
  std::vector<float> chunk_uv_;
  std::vector<float> chunk_index_;

  EDK3::ref_ptr<EDK3::dev::Buffer> buffer_;

  float map3d[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEEP];
};