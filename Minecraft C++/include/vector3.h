#include <math.h>

class Vector3{
public:
  Vector3(void);
  Vector3(float x, float y, float z);
  ~Vector3(void);
  float length();
  Vector3 normalize();
  float x, y, z;
};