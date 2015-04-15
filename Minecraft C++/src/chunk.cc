#include "../include/chunk.h"


Chunk::Chunk(){
  // Create the blocks
  cubes = new Cube**[CHUNK_SIZE];
  for (int i = 0; i < CHUNK_SIZE; i++){
    cubes[i] = new Cube*[CHUNK_SIZE];
    for (int j = 0; j < CHUNK_SIZE; j++){
      cubes[i][j] = new Cube[CHUNK_SIZE];
    }
  }
}

Chunk::~Chunk(){
  // Delete the blocks
  for (int i = 0; i < CHUNK_SIZE; ++i){
    for (int j = 0; j < CHUNK_SIZE; ++j){
      delete[] cubes[i][j];
    }
    delete[] cubes[i];
  }
  delete[] cubes;
}