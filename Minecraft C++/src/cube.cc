#include "../include/cube.h"

Cube::Cube(){}
Cube::~Cube(){}


bool Cube::isActive(){
  return m_active_;
}

void Cube::setActive(bool active){
  m_active_ = active;
}