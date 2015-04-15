

enum CubeType{
  kCubeType_Default = 0,

  kCubeType_Grass,
  kCubeType_Dirt,
  kCubeType_Water,
  kCubeType_Stone,
  kCubeType_Wood,
  kCubeType_Sand,

  kCubeType_NumTypes,
};

class Cube{
public:
  Cube();
  ~Cube();

  bool isActive();
  void setActive(bool active);

private:
  bool m_active_;

  CubeType cube_type_;
};