#include "../include/ichunk.h"

iChunk::iChunk(){
  octaves_ = 3.0f;
  persistence_ = 1.0f;
  scale_ = 0.02f;

  chunk_width_ = 1;
  chunk_height_ = 1;
  chunk_deep_ = 1;

  highest_level_ = 0.3;

  cube_side_size_ = 1;
}

void iChunk::setupNoise(float octaves, float persistence, float scale){
  octaves_ = octaves;
  persistence_ = persistence;
  scale_ = scale;
}

void iChunk::mapSize(int width, int height, int deep){
  chunk_width_ = width;
  chunk_height_ = height;
  chunk_deep_ = deep;
}

void iChunk::cubeSideSize(int size){
  cube_side_size_ = size;
}


void iChunk::setupMesh(){
  Cube cube_faces[6]; // 6 Sides on a cube
  
  int size = cube_side_size_;
  float pos = size*0.5f;
  float neg = size*-(0.5f);

  /*
    VERTEX
  */

  // Front side vertex
  float side_0_vert[12]{
    // face 1 (xy plane, z = 1 y = pos)
    neg, neg, pos, // 0 1 2
    pos, neg, pos, // 3 4 5
    pos, pos, pos, // 6 7 8
    neg, pos, pos // 9 10 11
  };
  cube_faces[0].vertex = &side_0_vert[0];

  // Right side vertex
  float side_1_vert[12]{
    // face 2 (zy plane, x=1 x=pos)
    pos, neg, pos, // 12 13 14
    pos, neg, neg, // 15 16 17
    pos, pos, neg, // 18 19 20
    pos, pos, pos // 21 22 23  
  };
  cube_faces[1].vertex = &side_1_vert[0];

  // Far side (back) vertex
  float side_2_vert[12]{
    // face 3 (xy plane, z=-1 z=neg)
    pos, neg, neg, // 24 25 26
    neg, neg, neg, // 27 28 29
    neg, pos, neg, // 30 31 32
    pos, pos, neg // 33 34 35
  };
  cube_faces[2].vertex = &side_2_vert[0];

  // Left side vertex
  float side_3_vert[12]{
    // face 4 (zy plane, x=-1 x=neg)
    neg, neg, neg, // 36 37 38
    neg, neg, pos, // 39 40 41
    neg, pos, pos, // 42 43 44
    neg, pos, neg // 45 46 47
  };
  cube_faces[3].vertex = &side_3_vert[0];

  // Top side vertex
  float side_4_vert[12]{
    // face 5  (zx plane, y=1 y=pos) UP Face
    neg, pos, pos, // 48 49 50
    pos, pos, pos, // 51 52 53
    pos, pos, neg, // 54 55 56
    neg, pos, neg // 57 58 59
  };
  cube_faces[4].vertex = &side_4_vert[0];

  // Bottom side vertex
  float side_5_vert[12]{
    // face 6 (zx plane, y=-1, y=neg) DOWN Face
    neg, neg, pos, // 60 61 62
    pos, neg, pos, // 63 64 65
    pos, neg, neg, // 66 67 68
    neg, neg, neg  // 69 70 71
  };
  cube_faces[5].vertex = &side_5_vert[0];

  /*
    UV's
  */
  // Now we will use the same UV for all the faces, 
  // We can improve this later
  float side_0_uv[8]{
    0, 0, // Face 1
    0, 1,
    1, 1,
    1, 0
  };

  /*
    NORMALS
  */

  // Front side normal
  float side_0_norm[12]{
    0, 0, 1, // Face 1
    0, 0, 1,
    0, 0, 1,
    0, 0, 1
  };
  cube_faces[0].normal = &side_0_norm[0];
  
  // Right side normal
  float side_1_norm[12]{
    1, 0, 0, // Face 2
    1, 0, 0,
    1, 0, 0,
    1, 0, 0
  };
  cube_faces[1].normal = &side_1_norm[0];

  // Far side (back) normal
  float side_2_norm[12]{
    0, 0, -1, // Face 3
    0, 0, -1,
    0, 0, -1,
    0, 0, -1
  };
  cube_faces[2].normal = &side_2_norm[0];

  // Left side vertex
  float side_3_norm[12]{
    -1, 0, 0, // Face 4
    -1, 0, 0,
    -1, 0, 0,
    -1, 0, 0
  };
  cube_faces[3].normal = &side_3_norm[0];

  // Top side normal
  float side_4_norm[12]{
    0, 1, 0, // Face 5
    0, 1, 0,
    0, 1, 0,
    0, 1, 0
  };
  cube_faces[4].normal = &side_4_norm[0];

  // Bottom side norm
  float side_5_norm[12]{
    0, -1, 0, // Face 6
    0, -1, 0,
    0, -1, 0,
    0, -1, 0
  };
  cube_faces[5].normal = &side_5_norm[0];


  // Chunk workaround

  std::vector<unsigned int> chunk_index;

  for (int z = 0; z < chunk_deep_; ++z) {
    for (int y = 0; y < chunk_height_; ++y) {
      for (int x = 0; x < chunk_width_; ++x) {
        
        float noise = octave_noise_3d(octaves_, persistence_, scale_, x, y, z);
        if (noise < highest_level_){
          bool all_faces[6] = {0,0,0,0,0,0};
          checkFace(x, y, z, all_faces);
          if (all_faces){
            for (int i = 0; i < 6; ++i){

              if (all_faces[i] == true){
                //printf("POS %d,%d,%d - face %d\n", x, y, z, i);
                // Vertex

                // Canela's method
                // This should calculate the indexes dynamically
                // I don't even know how it works

                for (int k = 0; k < 12; k++){
                  chunk_vertex_.push_back(cube_faces[i].vertex[k] + (x * size));
                  chunk_vertex_.push_back(cube_faces[i].vertex[++k] + (y * size));
                  chunk_vertex_.push_back(cube_faces[i].vertex[++k] + (z * size));
                }

                int p_size = chunk_vertex_.size() / 3;

                chunk_index.push_back(p_size - 4);
                chunk_index.push_back(p_size - 3);
                chunk_index.push_back(p_size - 2);

                chunk_index.push_back(p_size - 4);
                chunk_index.push_back(p_size - 2);
                chunk_index.push_back(p_size - 1);
                // End Canela's method

                // UV's
                for (int p = 0; p < 8; ++p){
                  chunk_uv_.push_back(side_0_uv[p]);
                }

                // Normals
                for (int q = 0; q < 12; ++q){
                  chunk_normal_.push_back(cube_faces[i].normal[q]);
                }

              }

            }
          }// END IF NOISE
        }

      }
    }
  } // End first FOR

  total_faces = chunk_vertex_.size() / 12;
  total_elements_ = chunk_vertex_.size() + chunk_normal_.size() + chunk_uv_.size();
  std::vector<float> cube_data(total_elements_);
  //int chunk_normal_i = 0;
  //int chunk_uv_i = 0;

  for (int i = 0, a = 0, b = 0; i < total_elements_; i++){
    if (i < chunk_vertex_.size()){
      cube_data[i] = chunk_vertex_[i];
    }
    if (i < chunk_uv_.size() + chunk_vertex_.size() && i >= chunk_vertex_.size()){
      cube_data[i] = chunk_uv_[a++];
      //chunk_uv_i++;
    }
    if (i < chunk_uv_.size() + chunk_vertex_.size() + chunk_normal_.size() && i >= chunk_uv_.size() + chunk_vertex_.size()){
      cube_data[i] = chunk_normal_[b++];
      //chunk_normal_i++;
    }
  }

  total_indexes_ = chunk_index.size();

  EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_);

  buffer_->init(sizeof(float)*total_elements_ + sizeof(unsigned int)*total_indexes_);
  buffer_->uploadData(&cube_data[0], sizeof(float)*total_elements_, 0);
  buffer_->uploadData(&chunk_index[0], sizeof(unsigned int)*total_indexes_, sizeof(float)*total_elements_);

}

void iChunk::checkFace(int x, int y, int z, bool* face_n){
  int faces_to_render = 0;

  // Face 0
  if (octave_noise_3d(octaves_, persistence_, scale_, x, y, z + 1) >= highest_level_ || z + 1 == chunk_deep_){
    face_n[0] = true; ++faces_to_render;
  }else{
    face_n[0] = false;
  }

  // Face 1
  if (octave_noise_3d(octaves_, persistence_, scale_, x + 1, y, z) >= highest_level_ || x + 1 == chunk_width_){
    face_n[1] = true; ++faces_to_render;
  }
  else{
    face_n[1] = false;
  }
 
  // Face 2
  if (octave_noise_3d(octaves_, persistence_, scale_, x, y, z - 1) >= highest_level_ || z - 1 == 0){
    face_n[2] = true; ++faces_to_render;
  }
  else{
    face_n[2] = false;
  }
  
  // Face 3
  if (octave_noise_3d(octaves_, persistence_, scale_, x - 1, y, z) >= highest_level_ || x - 1 == 0){
    face_n[3] = true; ++faces_to_render;
  }
  else{
    face_n[3] = false;
  }
  
  // Face 4
  if (octave_noise_3d(octaves_, persistence_, scale_, x, y + 1, z) >= highest_level_ || y + 1 == chunk_height_){
    face_n[4] = true; ++faces_to_render;
  }
  else{
    face_n[4] = false;
  }
  
  // Face 5
  if (octave_noise_3d(octaves_, persistence_, scale_, x, y - 1, z) >= highest_level_ || y - 1 == 0){
    face_n[5] = true; ++faces_to_render;
  }
  else{
    face_n[5] = false;
  }
  
}



bool iChunk::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute)const{

  switch (a){
  case EDK3::A_POSITION:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
      buffer_.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_3,
      false, 0, 0);
    return true;
  case EDK3::A_UV:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
      buffer_.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_2,
      false,
      sizeof(float) * 12 * total_faces,
      0); 
    return true;
  case EDK3::A_NORMAL:
    EDK3::dev::GPUManager::Instance()->enableVertexAttribute(
      buffer_.get(),
      where_to_bind_attribute,
      EDK3::T_FLOAT_3,
      true,
      sizeof(float) * ((12 * total_faces) + (8 * total_faces)),
      0);
    return true;
  }


  return false;
}

void iChunk::render() const{
  EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles, total_indexes_, buffer_.get(), EDK3::T_UINT, sizeof(float) * total_elements_);
}