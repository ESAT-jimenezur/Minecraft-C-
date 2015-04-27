#include "../include/cube.h"

Cube::Cube(){}
Cube::~Cube(){}
void Cube::CreateCube(int size){
  float pos = size*0.5;
  float neg = size*(-0.5);


  const unsigned int num_attributes_cube = 216;
  const unsigned int num_elements_cube = 36;

  const float cubepositions[num_attributes_cube] = {
    // face 1 (xy plane, z=1 y=pos)
    neg, neg, pos, // 0 1 2
    pos, neg, pos, // 3 4 5
    pos, pos, pos, // 6 7 8
    neg, pos, pos, // 9 10 11
    // face 2 (zy plane, x=1 x=pos)
    pos, neg, pos, // 12 13 14
    pos, neg, neg, // 15 16 17
    pos, pos, neg, // 18 19 20
    pos, pos, pos, // 21 22 23
    // face 3 (xy plane, z=-1 z=neg)
    pos, neg, neg, // 24 25 26
    neg, neg, neg, // 27 28 29
    neg, pos, neg, // 30 31 32
    pos, pos, neg, // 33 34 35
    // face 4 (zy plane, x=-1 x=neg)
    neg, neg, neg, // 36 37 38
    neg, neg, pos, // 39 40 41
    neg, pos, pos, // 42 43 44
    neg, pos, neg, // 45 46 47
    // face 5  (zx plane, y=1 y=pos) UP Face
    neg, pos, pos, // 48 49 50
    pos, pos, pos, // 51 52 53
    pos, pos, neg, // 54 55 56
    neg, pos, neg, // 57 58 59
    // face 6 (zx plane, y=-1, y=neg) DOWN Face
    neg, neg, pos, // 60 61 62
    pos, neg, pos, // 63 64 65
    pos, neg, neg, // 66 67 68
    neg, neg, neg,  // 69 70 71
    
    //UVs
    0, 0, // Face 1
    0, 1,
    1, 1,
    1, 0,
    0, 0, // Face 2
    0, 1,
    1, 1,
    1, 0,
    0, 0, // Face 3
    0, 1,
    1, 1,
    1, 0,
    0, 0, // Face 4
    0, 1,
    1, 1,
    1, 0,
    0, 0, // Face 5
    0, 1,
    1, 1,
    1, 0,
    0, 0, // Face 6
    0, 1,
    1, 1,
    1, 0,
    
    // Normals
    0, 0, 1, // Face 1
    0, 0, 1,
    0, 0, 1,
    0, 0, 1,
    1, 0, 0, // Face 2
    1, 0, 0,
    1, 0, 0,
    1, 0, 0,
    0, 0, -1, // Face 3
    0, 0, -1,
    0, 0, -1,
    0, 0, -1,
    -1, 0, 0, // Face 4
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0,
    0, 1, 0, // Face 5
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, -1, 0, // Face 6
    0, -1, 0,
    0, -1, 0,
    0, -1, 0,
  };

  const unsigned int cubeelements[num_elements_cube] = {
    0, 1, 3, 1, 2, 3,
    4, 5, 7, 5, 6, 7,
    8, 9, 11, 9, 10, 11,
    12, 13, 15, 13, 14, 15,
    16, 17, 19, 17, 18, 19,
    20, 21, 23, 21, 22, 23,
  };

  EDK3::dev::GPUManager::Instance()->newBuffer(&databuffer);
  EDK3::dev::GPUManager::Instance()->newBuffer(&elements);


  databuffer->init(sizeof(float)*num_attributes_cube);
  elements->init(sizeof(unsigned int)*num_elements_cube);

  /*databuffer->bind(EDK3::dev::Buffer::kTarget_Vertex_Data);
  elements->bind(EDK3::dev::Buffer::kTarget_Elements);
  */
  databuffer->uploadData(&cubepositions, sizeof(float)*num_attributes_cube);
  elements->uploadData(&cubeelements, sizeof(int)*num_elements_cube);
  
}


bool Cube::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const{

  switch (a){
  case EDK3::A_POSITION:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(databuffer.get(), 
      where_to_bind_attribute, EDK3::T_FLOAT_3, false, 0, 0);
    return true;
  case EDK3::A_UV:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(databuffer.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_2,
      false, sizeof(float)* 72, sizeof(float)* 2);
    return true;
  case EDK3::A_NORMAL:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(databuffer.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_3,
      true, sizeof(float)* 120, 0);
    return true;
  }


  return false;
}

void Cube::render()const{
  EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles,36, elements.get(), EDK3::T_UINT);
}