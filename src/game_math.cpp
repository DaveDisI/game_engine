#include "game_math.h"

void setOrthographicProjection(mat4& m, float left, float right, float bottom, float top){
  m.v[0][0] = 2 / (right - left);
  m.v[1][1] = 2 / (top - bottom);
  m.v[3][0] = -((right + left) / (right - left));
  m.v[3][0] = -((top + bottom) / (top - bottom));
}

void scale(mat4& m, vec3 s){
  m.v[0][0] *= s.v[0];
  m.v[1][1] *= s.v[1];
  m.v[2][2] *= s.v[2];
}

mat4 multiply(mat4& m1, mat4& m2){
  mat4 f;
  f.v[0][0] = (m1.v[0][0] * m2.v[0][0]) + (m1.v[0][1] * m2.v[1][0]) + (m1.v[0][2] * m2.v[2][0]) + (m1.v[0][3] * m2.v[3][0]);
  f.v[0][1] = (m1.v[0][0] * m2.v[0][1]) + (m1.v[0][1] * m2.v[1][1]) + (m1.v[0][2] * m2.v[2][1]) + (m1.v[0][3] * m2.v[3][1]);
  f.v[0][2] = (m1.v[0][0] * m2.v[0][2]) + (m1.v[0][1] * m2.v[1][2]) + (m1.v[0][2] * m2.v[2][2]) + (m1.v[0][3] * m2.v[3][2]);
  f.v[0][3] = (m1.v[0][0] * m2.v[0][3]) + (m1.v[0][1] * m2.v[1][3]) + (m1.v[0][2] * m2.v[2][3]) + (m1.v[0][3] * m2.v[3][3]);

  f.v[1][0] = (m1.v[1][0] * m2.v[0][0]) + (m1.v[1][1] * m2.v[1][0]) + (m1.v[1][2] * m2.v[2][0]) + (m1.v[1][3] * m2.v[3][0]);
  f.v[1][1] = (m1.v[1][0] * m2.v[0][1]) + (m1.v[1][1] * m2.v[1][1]) + (m1.v[1][2] * m2.v[2][1]) + (m1.v[1][3] * m2.v[3][1]);
  f.v[1][2] = (m1.v[1][0] * m2.v[0][2]) + (m1.v[1][1] * m2.v[1][2]) + (m1.v[1][2] * m2.v[2][2]) + (m1.v[1][3] * m2.v[3][2]);
  f.v[1][3] = (m1.v[1][0] * m2.v[0][3]) + (m1.v[1][1] * m2.v[1][3]) + (m1.v[1][2] * m2.v[2][3]) + (m1.v[1][3] * m2.v[3][3]);

  f.v[2][0] = (m1.v[2][0] * m2.v[0][0]) + (m1.v[2][1] * m2.v[1][0]) + (m1.v[2][2] * m2.v[2][0]) + (m1.v[2][3] * m2.v[3][0]);
  f.v[2][1] = (m1.v[2][0] * m2.v[0][1]) + (m1.v[2][1] * m2.v[1][1]) + (m1.v[2][2] * m2.v[2][1]) + (m1.v[2][3] * m2.v[3][1]);
  f.v[2][2] = (m1.v[2][0] * m2.v[0][2]) + (m1.v[2][1] * m2.v[1][2]) + (m1.v[2][2] * m2.v[2][2]) + (m1.v[2][3] * m2.v[3][2]);
  f.v[2][3] = (m1.v[2][0] * m2.v[0][3]) + (m1.v[2][1] * m2.v[1][3]) + (m1.v[2][2] * m2.v[2][3]) + (m1.v[2][3] * m2.v[3][3]);

  f.v[3][0] = (m1.v[3][0] * m2.v[0][0]) + (m1.v[3][1] * m2.v[1][0]) + (m1.v[3][2] * m2.v[2][0]) + (m1.v[3][3] * m2.v[3][0]);
  f.v[3][1] = (m1.v[3][0] * m2.v[0][1]) + (m1.v[3][1] * m2.v[1][1]) + (m1.v[3][2] * m2.v[2][1]) + (m1.v[3][3] * m2.v[3][1]);
  f.v[3][2] = (m1.v[3][0] * m2.v[0][2]) + (m1.v[3][1] * m2.v[1][2]) + (m1.v[3][2] * m2.v[2][2]) + (m1.v[3][3] * m2.v[3][2]);
  f.v[3][3] = (m1.v[3][0] * m2.v[0][3]) + (m1.v[3][1] * m2.v[1][3]) + (m1.v[3][2] * m2.v[2][3]) + (m1.v[3][3] * m2.v[3][3]);
  return f;
}