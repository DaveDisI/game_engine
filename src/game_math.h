#pragma once

struct vec2{
  float v[2] = {0, 0};
  vec2(int x = 0, int y = 0){
    v[0] = x;
    v[1] = y;
  }
};

struct vec3{
  float v[3] = {0, 0, 0};
  vec3(int x = 0, int y = 0, int z = 0){
    v[0] = x;
    v[1] = y;
    v[2] = z;
  }
};

struct vec4{
  float v[4] = {0, 0, 0, 0};
  vec4(int x = 0, int y = 0, int z = 0, int w = 0){
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

  mat4(int id = 0){
    v[0][0] = v[1][1] = v[2][2] = v[3][3] = id;
  }
};

void setOrthographicProjection(mat4& m, float left, float right, float bottom, float top);

void scale(mat4& m, vec3 s);

mat4 multiply(mat4& m1, mat4& m2);
