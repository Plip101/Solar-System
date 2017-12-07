#pragma once
#ifndef Enemy_H
#define Enemy_H
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

class Enemy : public GameObject
{
private:
	float speed;
	vec3 distance;
public:
	Enemy(float speed, vec3 distanceParam, string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,
		vec3 colorParam);

	void render();
	void update();

	float getSpeed();
	vec3 getDistance();
	
	void setSpeed(float speedParam);
	void setDistance(vec3 distanceParam);


};

#endif