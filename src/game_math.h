#pragma once

#include <math.h>

struct vec2{
  float v[2] = {0, 0};
  vec2(float x = 0, float y = 0){
    v[0] = x;
    v[1] = y;
  }
};

struct vec3{
  float v[3] = {0, 0, 0};
  vec3(float x = 0, float y = 0, float z = 0){
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }
  vec3(vec2 vec, float z = 0){
    v[0] = vec.v[0];
    v[1] = vec.v[1];
    v[2] = z;
  }
};

struct vec4{
  float v[4] = {0, 0, 0, 0};
  vec4(float x = 0, float y = 0, float z = 0, float w = 0){
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
  }
};

struct quat{
  float v[4] = {0, 0, 0, 0};
  quat(float x = 0, float y = 0, float z = 0, float w = 0){
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = w;
  }
};

struct mat4{
  float v[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
  };

  mat4 operator* (mat4& m);

  mat4(float id = 0){
    v[0][0] = v[1][1] = v[2][2] = v[3][3] = id;
  }
};


void setOrthographicProjection(mat4& m, float left, float right, float bottom, float top);
void setPerspectiveProjection(mat4& m, float fov, float aspect, float near, float far);
void rotate(mat4& m, float rotation, vec3 r);
void scale(mat4& m, vec3 s);
void translate(mat4& m, vec3 t);
mat4 inverse(mat4& m);
mat4 multiply(mat4& m1, mat4& m2);
