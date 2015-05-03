#ifndef __ICHUNK_H__
#define __ICHUNK_H__

#include <vector>

#include <EDK3\geometry.h>

#include <EDK3\dev\gpumanager.h>
#include "EDK3\dev\buffer.h"

#include "simplexnoise.h"

struct Cube{
  float* vertex;
  float* normal;
};

class iChunk : public EDK3::Geometry{

public:
  iChunk();
  ~iChunk(){};

  void setupNoise(float octaves, float persistence, float scale);
  void mapSize(int width, int height, int deep);
  void cubeSideSize(int size);
  void setupMesh();
  void init();
  

  virtual bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const;
  virtual void render() const;
  
private:

  // Noise Values
  float octaves_;
  float persistence_;
  float scale_;

  // Map Size
  int chunk_width_;
  int chunk_height_;
  int chunk_deep_;

  std::vector<float> chunk_vertex_;
  std::vector<float> chunk_normal_;
  std::vector<float> chunk_uv_;

  unsigned int total_faces;
  unsigned int total_elements_;
  unsigned int total_indexes_;

  EDK3::ref_ptr<EDK3::dev::Buffer> buffer_;

  int highest_level_;

  int cube_side_size_;

  void checkFace(int x, int y, int z, bool* face_n);
};


#endif // ENDIF