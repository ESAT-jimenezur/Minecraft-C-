#include "../include/Vector3.h"

Vector3::Vector3(void){}

Vector3::Vector3(float x, float y, float z){
  this->x = x;
  this->y = y;
  this->z = z;
}

// Returns the length of the vector
float Vector3::length(){
  return sqrt(x * x + y * y + z * z);
}

// Normalizes the vector
Vector3 Vector3::normalize(){
  Vector3 vector;
  float length = this->length();

  if (length != 0){
    vector.x = x / length;
    vector.y = y / length;
    vector.z = z / length;
  }

  return vector;
}

Vector3::~Vector3(void){}