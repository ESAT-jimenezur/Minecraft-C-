#ifndef INCLUDE_EDK3_CAMERA_H_
#define INCLUDE_EDK3_CAMERA_H_ 1

// ----------------------------------------------------------------------------
// Copyright (C) 2014 Jose L. Hidalgo 
// Camera Class.
// ----------------------------------------------------------------------------
//
#include "Referenced.h"
#include <vector>

namespace EDK3 {

  class Node;

  class Camera : public virtual Referenced {
  public:
    Camera();
    void setupPerspective(float fovy, float aspect, float znear, float zfar);
    void setupOrtho(
        float left,   float right,
        float bottom, float top,
        float znear,  float zfar);
    void setupFrustum(
        float left, float right,
        float bottom, float top,
        float znear, float zfar);

    void set_position(const float pos[3]);
    void set_view_direction(const float pos[3]);
    void set_view_target(const float pos[3]);
    void set_up_direction(const float pos[3]);
    void set_clear_flags(bool color, bool depth, bool stencil);
    void set_clear_color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

    const float *position() const;
    const float *target() const;
    const float *up_direction() const;

    void set_projection_matrix(const float data[16]);
    const float *projection_matrix() const;

    void set_view_matrix(const float data[16]);
    const float *view_matrix() const;

    /** determine which objects are visible */
    virtual void doCull(const Node *root_node);

    /** renders all visible (not culled) objects */
    virtual void doRender() const;

    // hidden camera structure data
    struct Data;
  protected:
    virtual ~Camera();

  private:
    Data * const data_;
    Camera(const Camera&);
    Camera& operator=(const Camera&);
  };


} /* end of EDK3 Namespace */

#endif
