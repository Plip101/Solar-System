#pragma once
#ifndef Planet_H
#define Planet_H
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
#include "GameObject.h"
using namespace std;
using namespace glm;

class Planet : public GameObject
{
private:
	float os, rs, oa;
public:
	Planet(float osParam, float rsParam, float oaParam, string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,
		vec3 colorParam);

	void render();
	void update();

	float getOs();
	float getRs();
	float getOa();

	void setOs(float osParam);
	void setRs(float rsParam);
	void setOa(float oaParam);
	
	
};

#endif