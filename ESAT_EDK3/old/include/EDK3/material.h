#ifndef INCLUDE_EDK3_MATERIAL_H_
#define INCLUDE_EDK3_MATERIAL_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Material Class.
// ----------------------------------------------------------------------------

#include "referenced.h"
#include "constants.h"

namespace EDK3 {

  class MaterialSettings;
  class Camera;
  class Drawable;

  class Material : public virtual Referenced {
  public:
    // Returns true if the material can be set with the given material
    // settings
    virtual bool enable(const MaterialSettings *) const = 0;
    // called after enable to setup the camera matrix
    virtual void setupCamera(const Camera*) const = 0;
    // called after enable to setup the model matrix
    // model is the transform from local->world coordinates
    virtual void setupModel(const float model[16]) const = 0;
    
    virtual unsigned int num_attributes_required() const = 0;
    virtual Attribute attribute_at_index(
        const unsigned int attrib_idx) const = 0;
    virtual Type attribute_type_at_index(
        const unsigned int attrib_index) const = 0;

  protected:
    Material() {}
    virtual ~Material() {}
  private:
    Material(const Material&);
    Material& operator=(const Material &);
  };

} /* end of EDK Namespace */

#endif
