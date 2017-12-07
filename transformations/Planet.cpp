#include "Planet.h"
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
Planet::Planet(float osParam, float rsParam, float oaParam, string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,	vec3 colorParam)
	:GameObject(nameParam,scaleParam,rotationParam,transParam,colorParam)
{
	os = osParam;
	rs = rsParam;
	oa = oaParam;
}
void Planet::setOs(float osParam)
{
	os = osParam;
}
void Planet::setRs(float rsParam)
{
	rs += rsParam;
}
void Planet::setOa(float oaParam)
{
	oa = oaParam;
}


float Planet::getOs()
{
	return os;
}
float Planet::getRs()
{
	return rs;
}
float Planet::getOa()
{
	return oa;
}