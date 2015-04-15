#include "cube.h"

class Chunk{
public:
  Chunk();
  ~Chunk();

  void update(float dt);
  void render();
  void createCube();
  

  static const int CHUNK_SIZE = 16;

private:
  // The blocks data
  Cube*** cubes;
};