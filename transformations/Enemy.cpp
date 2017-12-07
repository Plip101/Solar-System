#include "Enemy.h"
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
Enemy::Enemy(float speedParam,vec3 distanceParam, string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam, vec3 colorParam)
	:GameObject(nameParam, scaleParam, rotationParam, transParam, colorParam)
{
	speed = speedParam;
	distance = distanceParam;
}
void Enemy::setSpeed(float speedParam)
{
	speed = speedParam;
}
void Enemy::setDistance(vec3 distanceParam)
{
	distance = distanceParam;
}

float Enemy::getSpeed()
{
	return speed;
}

vec3 Enemy::getDistance()
{
	return distance;
}