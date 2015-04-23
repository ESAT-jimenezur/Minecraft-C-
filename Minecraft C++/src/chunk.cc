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
  for (int x = 0; x < CHUNK_WIDTH; ++x) {
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
      for (int z = 0; z < CHUNK_DEEP; ++z) {
        noise = octave_noise_3d(3, 1, 0.02f, x, y, z);
        if (noise <= 0.3f){
          //createCube(x * 5, y * 5, z * 5);
          map3d[CHUNK_WIDTH][CHUNK_HEIGHT][CHUNK_DEEP] = 1.0f; // 1 -> CUBE
        }
      }
    }
  }
}

void Chunk::createMesh(){
  for (int x = 0; x < CHUNK_WIDTH; ++x) {
    for (int y = 0; y < CHUNK_HEIGHT; ++y) {
      for (int z = 0; z < CHUNK_DEEP; ++z) {
        noise = octave_noise_3d(3, 1, 0.02f, x, y, z);
        if (noise <= 0.3f){
          
        }
      }
    }
  }
}