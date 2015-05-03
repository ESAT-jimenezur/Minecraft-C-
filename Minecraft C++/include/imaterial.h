#ifndef __IMATERIAL_H__
#define __IMATERIAL_H__

#include "stdio.h"
#include "conio.h"
#include <EDK3\geometry.h>
#include <EDK3\camera.h>
#include <EDK3\drawable.h>
#include <EDK3\matdiffusetexture.h>
#include <EDK3\texture.h>
#include <EDK3\dev\gpumanager.h>
#include "EDK3\dev\buffer.h"
#include <EDK3\dev\shader.h>
#include <EDK3\dev\program.h>
#include <EDK3\dev\glew.h>
#include <EDK3\dev\opengl.h>
#include <EDK3\materialsettings.h>



  class iMaterial : public EDK3::Material{

  public:
    iMaterial();

    unsigned int num_attributes_required() const;
    EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const;
    EDK3::Type attribute_type_at_index(const unsigned int attrib_idx) const;

    bool enable(const EDK3::MaterialSettings *mat_settings) const;
    void setupCamera(const float projecton[16], const float view[16]) const;
    void setupModel(const float m[16]) const;


    class Settings : public EDK3::MaterialSettings {
    public:
      Settings() {}
      void set_color(const float v[4]) { memcpy(data_, v, sizeof(data_)); }
      const float *color() const { return data_; }

      // Texture
      void set_texture(EDK3::Texture *t) { texture_ = t; }
      EDK3::Texture* texture() { return texture_.get(); }
      const EDK3::Texture* texture() const { return texture_.get(); }

      void set_normal_texture(EDK3::Texture *t) { normal_texture_ = t; }
      EDK3::Texture* normal_texture() { return normal_texture_.get(); }
      const EDK3::Texture* normal_texture() const { return normal_texture_.get(); }
    protected:
      virtual ~Settings() {}
    private:
      Settings(const Settings&);
      Settings& operator=(const Settings&);
      float data_[4];
      EDK3::ref_ptr<EDK3::Texture> texture_;
      EDK3::ref_ptr<EDK3::Texture> normal_texture_;
    };

  private:
    ~iMaterial(){}
    EDK3::ref_ptr<EDK3::dev::Program> program_;
    EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader_;
    EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader_;

  };
#endif //__IMATERIAL_H__