#pragma once
#ifndef Player_H
#define Player_H
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

class Player : public GameObject
{
private:
	float speed;
public:
	Player(float speed, string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,
		vec3 colorParam);

	void render();
	void update();

	float getSpeed();

	void setSpeed(float speedParam);


};

#endif