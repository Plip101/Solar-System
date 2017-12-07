#include "Player.h"
#include "GameObject.h"
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
Player::Player(float speedParam,string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam, vec3 colorParam)
	:GameObject(nameParam, scaleParam, rotationParam, transParam, colorParam)
{
	speed = speedParam;
}
void Player::setSpeed(float speedParam)
{
	speed = speedParam;
}

float Player::getSpeed()
{
	return speed;
}