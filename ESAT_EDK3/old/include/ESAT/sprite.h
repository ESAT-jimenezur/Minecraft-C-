/* Copyright 2014 ESAT. All rights reserved.    #####  #####      #     #####
 * Author: Jose L. Hidalgo <jlhidalgo@esat.es>  #      #         # #      #
 *                                              ###     ###     #   #     #
 * Sprite commands                              #          #   #     #    #
 *                                              #####  #####  #       #   #
 */

#ifndef ESAT_SPRITE_H
#define ESAT_SPRITE_H 1

#include <ESAT/math.h>

namespace ESAT {

  typedef int SpriteHandle;

  SpriteHandle SpriteFromFile(const char *path);
  SpriteHandle SpriteFromMemory(int width, int height, const unsigned char *data_RGBA = 0L);
  void SpriteUpdateFromMemory(SpriteHandle, const unsigned char *data_RGBA);

  void SpriteRelease(SpriteHandle img);
  int SpriteHeight(SpriteHandle img);
  int SpriteWidth(SpriteHandle img);
  void DrawSprite(SpriteHandle img, float x, float y);

  // Draws an Sprite with a transformation matrix. The matrix values are specified as
  // a column-major 3x3 matrix. Only six values are used as shown:
  //     | m1 m3 m5 |
  // M = | m2 m4 m6 |  --> m = [m1,m2,m3,m4,m5,m6]
  //     | 0   0  1 |

  void DrawSpriteWithTransform(SpriteHandle img, const float tranform_matrix[6]);

  // Draws an Sprite with ESAT::Mat3 as input
  void DrawSpriteWithTransform(SpriteHandle img, const ESAT::Mat3 &m);

} /* ESAT */

#endif