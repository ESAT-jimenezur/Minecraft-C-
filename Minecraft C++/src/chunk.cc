#include "../include/chunk.h"


Chunk::Chunk(){
  noise = 0;
}

void Chunk::init(){
  //Empty array
  for (int x = 0; x < CHUNK_WIDTH; x++) {
    for (int y = 0; y < CHUNK_HEIGHT; y++) {
      for (int z = 0; z < CHUNK_DEEP; z++) {
        map3d[x][y][z] = 0;
      }
    }
  }
}

Chunk::~Chunk(){

}

void Chunk::createCube(float x, float y, float z){

  // Create a cube
  EDK3::ref_ptr<EDK3::Geometry> geo;
  EDK3::CreateCube(&geo, 5, true, true);
  // Material
  EDK3::ref_ptr<iMaterial> mat;
  EDK3::ref_ptr<iMaterial::Settings> mat_settings;

  mat.alloc();
  mat_settings.alloc();
  float color[] = { 255.0, 0.0, 0.0, 1.0 };
  mat_settings->set_color(color);

  EDK3::ref_ptr<EDK3::Drawable> drawable;
  mat_settings.alloc();
  mat_settings->set_color(color);
  drawable.alloc();
  drawable->set_geometry(geo.get());
  drawable->set_material(mat.get());
  drawable->set_material_settings(mat_settings.get());
  drawable->set_position(x, y, z);
  drawable->set_HPR(0.0f, 0.0f, 0.0f);
  GameManager::Instance()->game_state().root->addChild(drawable.get()); 
  //printf("Cube Created \n");
}

void Chunk::setupNoise(){
  // -0.3 Cube; aire
  createCube(10 * 5, 5, 5);
  
  for (int x = 0; x < CHUNK_WIDTH; ++x) {
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
      for (int z = 0; z < CHUNK_DEEP; ++z) {
        noise = octave_noise_3d(3, 1, 0.02f, x, y, z);
        if (noise <= 0.3f){
          createCube(x * 5, y * 5, z * 5);
          //map3d[x][y][z] = 1.0f;
        }
        else{
          map3d[x][y][z] = noise;
        }
      }
    }
  }
}

void Chunk::createMesh(){
  int size = 1;
  float pos = size*0.5;
  float neg = size*(-0.5);


  const unsigned int num_attributes_cube = 216;
  const unsigned int num_elements_cube = 36;

  const unsigned int num_vertex = 72;
  const unsigned int num_uvs = 48;
  const unsigned int num_normals = 72;

  const float vertex[num_vertex] = {
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
    neg, neg, neg  // 69 70 71
  };

  const float uvs[num_uvs]{
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
    1, 0
  };

  const float normals[num_normals]{
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
    0, -1, 0
  };




  for (int x = 0; x < CHUNK_WIDTH; ++x) {
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
      for (int z = 0; z < CHUNK_DEEP; ++z) {
        //printf("%f\n", map3d[x][y][z]);
        // Cube
        if (map3d[x][y][z] == 1.0f){
        
          //if (map3d[x + 1][y][z] != 1.0f){

            for (int i = 0; i < 12; i++){
              chunk_vertex_.push_back(vertex[i + (12*2)]); // *2-> 2a cara
            }
            for (int i = 0; i < 8; i++){
              chunk_uv_.push_back(uvs[i +(8*2)]); // *2-> 2a cara
            }
            for (int i = 0; i < 12; i++){
              chunk_normal_.push_back(normals[i + (12 * 2)]); // *2-> 2a cara
            }

            int p_size = chunk_vertex_.size() / 3;

            chunk_index_.push_back(p_size - 4);
            chunk_index_.push_back(p_size - 3);
            chunk_index_.push_back(p_size - 2);

            chunk_index_.push_back(p_size - 4);
            chunk_index_.push_back(p_size - 2);

            chunk_index_.push_back(p_size - 1);

          //}

        
        }

      }
    }
  }
  
  EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_);

  buffer_->init(sizeof(float)*num_attributes_cube);

  buffer_->uploadData(&chunk_vertex_, sizeof(chunk_vertex_)*12 + 0);
  buffer_->uploadData(&chunk_uv_, sizeof(chunk_uv_)* 8 + sizeof(chunk_index_));
  buffer_->uploadData(&chunk_normal_, sizeof(chunk_normal_)* 12 + sizeof(chunk_uv_));
  buffer_->uploadData(&chunk_index_, sizeof(chunk_index_)* 12 + sizeof(chunk_normal_));


  for (int i = 0; i < chunk_uv_.size(); i++){
    printf("%f\n", chunk_uv_[i]);
  }

}

bool Chunk::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const{

  switch (a){
  case EDK3::A_POSITION:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(buffer_.get(),
      where_to_bind_attribute, EDK3::T_FLOAT_3, false, 0, 0);
    return true;
  case EDK3::A_UV:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(buffer_.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_2,
      false, sizeof(float)* 72, sizeof(float)* 2);
    return true;
  case EDK3::A_NORMAL:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(buffer_.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_3,
      true, sizeof(float)* 120, 0);
    return true;
  }


  return false;
}

void Chunk::render(){
  EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, 36, buffer_.get(), EDK3::T_UINT);
}