#ifndef INCLUDE_EDK3_MAT_DIFFUSE_H_
#define INCLUDE_EDK3_MAT_DIFFUSE_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Diffuse Material Implementation
// ----------------------------------------------------------------------------

#include "ref_ptr.h"
#include "material.h"
#include "materialsettings.h"
#include "dev/program.h"

namespace EDK3 {

  class MatDiffuse : public Material {
  public:
    MatDiffuse();
    bool enable(const MaterialSettings *) const;
    void setupCamera(const Camera*) const;
    void setupModel(const float m[16]) const;

    unsigned int num_attributes_required() const;
    Attribute attribute_at_index(
        const unsigned int attrib_idx) const;
    Type attribute_type_at_index(
        const unsigned int attrib_index) const;

    class Settings : public MaterialSettings {
    public:
      Settings() {}
      void set_color(const float v[4]) { memcpy(data_, v, sizeof(data_)); }
      const float *color() const { return data_; }
    protected:
      virtual ~Settings() {}
    private:
      Settings(const Settings&);
      Settings& operator=(const Settings&);
      float data_[4];
    };

  protected:
    virtual ~MatDiffuse() {}
  private:
    ref_ptr<dev::Program> program_;
    MatDiffuse(const MatDiffuse&);
    MatDiffuse& operator=(const MatDiffuse &);
  };

} /* end of EDK Namespace */

#endif
