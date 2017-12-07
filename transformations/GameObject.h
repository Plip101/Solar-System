#pragma once
#ifndef GameObject_H
#define GameObject_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Windows.h>
#include "aiterror.h"
#include "aitmesh.h"
#include <math.h>
using namespace std;
using namespace glm;

class GameObject
{
private:
	//scale
	//rotation
	//trans
	//color
	//name
	string name, path;
	vec3 scale, rotation, trans, color;
	mat4 transformation;
	
public:
	//update
	//setters + getters
	//transformation(scale_param:vec3, trans_param:vec3, rotation_param:vec3) : void
	//render

	/*GameObject(string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,
		vec3 colorParam, mat4 transformationParam);*/
	//GameObject(string nameParam, vec3 colorParam, mat4 transformationParam);
	GameObject(string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,
		vec3 colorParam);
	string getName();
	vec3 getScale();
	vec3 getRotation();
	vec3 getTrans();
	vec3 getColor();
	mat4 getTransformation();

	void setName(string nameParam);
	void setScale(vec3 scaleParam);
	void setRotation(vec3 rotationParam);
	void setTrans(vec3 transParam);
	void setColor(vec3 colorParam);
	void setTransformation(mat4 transformationParam);
	void update();
	static void render(mat4 numParam);
	void createVertexBuffer();

	
	
};

#endif