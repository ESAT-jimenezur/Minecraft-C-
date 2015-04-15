/* Copyright 2015 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #
 * Math reference methods                       #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_MATH_H
#define ESAT_MATH_H 1

namespace ESAT {

  struct Mat3 { float d[9]; };
  void Mat3Multiply(const Mat3 &a, const Mat3 &b, Mat3 *output);

  void Mat3SetIdentity(Mat3 *output);
  void Mat3SetTranslate(float translate_x, float translate_y, Mat3 *output);
  void Mat3SetRotate(float radians, Mat3 *output);
  void Mat3SetScale(float scale_x, float scale_y, Mat3 *output);

  void Mat3Translate(float translate_x, float translate_y, Mat3 *in_out);
  void Mat3Rotate(float radians, Mat3 *in_out);
  void Mat3Scale(float scale_x, float scale_y, Mat3 *in_out);

  void Mat3Copy(const Mat3 &origin, Mat3 *dst);
  void Mat3TransformVec3(const Mat3 &a, const float v[3], float v_output[3]);
  void Mat3TransformVec2(const Mat3 &a, const float v[2], float v_output[2]);


  struct Mat4 { float d[16]; };
  void Mat4Multiply(const Mat4 &a, const Mat4 &b, Mat4 *output);

  void Mat4SetIdentity(Mat4 *output);
  void Mat4SetTranslate(float translate_x, float translate_y, float translate_z, Mat4 *output);
  void Mat4SetRotateX(float radians, Mat4 *output);
  void Mat4SetRotateY(float radians, Mat4 *output);
  void Mat4SetRotateZ(float radians, Mat4 *output);
  void Mat4SetScale(float scale_x, float scale_y, float scale_z, Mat4 *output);

  void Mat4Translate(float translate_x, float translate_y, float translate_z, Mat4 *in_out);
  void Mat4RotateX(float radians, Mat4 *in_out);
  void Mat4RotateY(float radians, Mat4 *in_out);
  void Mat3RotateZ(float radians, Mat4 *in_out);
  void Mat4Scale(float scale_x, float scale_y, float scale_z, Mat4 *in_out);

  void Mat4Copy(const Mat4 &origin, Mat4 *dst);
  void Mat4TransformVec4(const Mat4 &a, const float v[4], float v_output[4]);
  void Mat4TransformVec3(const Mat4 &a, const float v[3], float v_output[3]);



} /* ESAT */

#endif
