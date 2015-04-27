#ifndef __CUBE_H__
#define __CUBE_H__

#include "stdio.h"
#include "conio.h"
#include <EDK3\geometry.h>
#include <EDK3\camera.h>
#include <EDK3\drawable.h>
#include <EDK3\matdiffusetexture.h>
#include <EDK3\texture.h>
#include <EDK3\dev\gpumanager.h>
#include "EDK3\dev\buffer.h"



class Cube : virtual public EDK3::Geometry{

public:

  Cube();

  virtual bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const;

  virtual void render()const;
  void CreateCube(int size);

protected:
  virtual ~Cube();

private:
  EDK3::ref_ptr<EDK3::dev::Buffer> databuffer;
  EDK3::ref_ptr<EDK3::dev::Buffer> elements;
};


#endif //__CUBE_H__