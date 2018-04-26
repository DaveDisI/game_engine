#pragma once

#include "game_math.h"

struct Camera2D {
	float rotation = 0;
	vec2 position = vec2(0);
	mat4 viewMatrix = mat4(1);
	mat4 projectionMatrix = mat4(1);

	void setProjection(float left, float right, float bottom, float top){
		setOrthographicProjection(projectionMatrix, left, right, bottom, top);
	}

	void update(){
		viewMatrix = mat4(1);
		translate(viewMatrix, vec3(position.v[0], position.v[1], 0));
		rotate(viewMatrix, rotation, vec3(0, 0, 1));
	}
};

struct Camera3D{
	vec3 position = vec3(0);
	quat orientation = quat();
	mat4 viewMatrix = mat4(1);
	mat4 perspectiveMatrix = mat4(1);

	void setPerspective(float fov, float aspect, float near, float far){
		 setPerspectiveProjection(perspectiveMatrix, fov, aspect, near, far);
	}

	void update(){
		viewMatrix = mat4(1);
		translate(viewMatrix, position);
	}
};
