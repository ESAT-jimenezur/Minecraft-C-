#include "../include/imaterial.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

iMaterial::iMaterial(){
  EDK3::dev::GPUManager::Instance()->newProgram(&program_);
  EDK3::dev::GPUManager::Instance()->newShader(&vertex_shader_);
  EDK3::dev::GPUManager::Instance()->newShader(&fragment_shader_);


  /* SPECULAR FRAGMENT LOAD*/
  std::stringstream fragment_streamstring;
  std::string fragment_string;
  std::ifstream fragment_file("shaders/specular_fragment.sha");
  if (fragment_file.is_open()){
    fragment_streamstring << fragment_file.rdbuf();
    fragment_file.close();

    fragment_string = fragment_streamstring.str();
  }
  const char* fragment_shader_src = fragment_string.c_str();;
  fragment_shader_->loadSource(EDK3::dev::Shader::Type::kType_Fragment, fragment_shader_src, strlen(fragment_shader_src));

  /* SPECULAR VERTEX LOAD*/
  std::stringstream vertex_streamstring;
  std::string vertex_string;
  std::ifstream vertex_file("shaders/specular_vertex.sha");
  if (vertex_file.is_open()){
    vertex_streamstring << vertex_file.rdbuf();
    vertex_file.close();

    vertex_string = vertex_streamstring.str();
  }
  const char* vertex_shader_src = vertex_string.c_str();
  vertex_shader_->loadSource(EDK3::dev::Shader::Type::kType_Vertex, vertex_shader_src, strlen(vertex_shader_src));




  EDK3::scoped_array<char> log;

  if (!vertex_shader_->compile(&log)){
    printf("No ha compilado (VERTEX) \n");
  }
  printf("%s", log);
  log.memClear();

  if (!fragment_shader_->compile(&log)){
    printf("No ha compilado (FRAGMENT) \n");
  }
  printf("%s", log);
  log.memClear();

  program_->attach(fragment_shader_.get());
  program_->attach(vertex_shader_.get());


  if (!program_->link(&log)){
    printf("%s\n", log);
  }

}

unsigned int iMaterial::num_attributes_required() const {
  return 2;
}

EDK3::Attribute iMaterial::attribute_at_index(const unsigned int attrib_idx) const {
  switch (attrib_idx) {
  case 0:
    return EDK3::A_POSITION;
  case 1:
    return EDK3::A_NORMAL;
  }

  return EDK3::A_NONE;
}

EDK3::Type iMaterial::attribute_type_at_index(const unsigned int attrib_idx) const {
  switch (attrib_idx) {
    case 0: 
      return EDK3::T_FLOAT_3;
    case 1: 
      return EDK3::T_FLOAT_3;
  }
  return EDK3::T_NONE;
}

bool iMaterial::enable(const EDK3::MaterialSettings *mat_settings)const{
  program_->use();

  //int color = program_->get_uniform_position("u_color");
  //const Settings* settings = dynamic_cast<const Settings*>(mat_settings);

  //program_->set_uniform_value(color, EDK3::Type::T_FLOAT_4, settings->color());

  return true;
}

void iMaterial::setupCamera(const EDK3::Camera* camera) const{
  int view_ = program_->get_uniform_position("u_view_matrix");
  program_->set_uniform_value(view_, EDK3::Type::T_MAT_4x4, camera->view_matrix());

  int projection_ = program_->get_uniform_position("u_projection_matrix");
  program_->set_uniform_value(projection_, EDK3::Type::T_MAT_4x4, camera->projection_matrix());
}

void iMaterial::setupModel(const float m[16]) const{
  int model_mat = program_->get_uniform_position("u_model_matrix");
  program_->set_uniform_value(model_mat, EDK3::Type::T_MAT_4x4, m);
}