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

GameObject::GameObject(string nameParam, vec3 scaleParam, vec3 rotationParam, vec3 transParam,
	vec3 colorParam)
{
	name = nameParam;
	scale = scaleParam;
	rotation = rotationParam;
	trans = transParam;
	color = colorParam;
}


void GameObject::setName(string nameParam)
{
	name = nameParam;
}
void GameObject::setScale(vec3 scaleParam)
{
	scale = scaleParam;
}
void GameObject::setRotation(vec3 rotationParam)
{
	rotation = rotationParam;
}
void GameObject::setTrans(vec3 transParam)
{
	trans += transParam;
}
void GameObject::setColor(vec3 colorParam)
{
	color = colorParam;
}

/*void GameObject::createVertexBuffer()
{
	GLuint VBO;
	int NUMVERTS = 3;
	float zaxis = 40.0f;
	float yaxis = 10.0f;
	float xaxis = 0.0f;
	GLuint gModelToWorldTransformLocation;
	GLuint gWorldToViewTransformLocation;
	GLuint gProjectionTransformLocation;
	GLuint gColorLocation;
	aitMesh mesh;
	if (!mesh.loadFromObj("assets/box.obj"))
	{
		cerr << "Error loading mesh from obj file." << endl;
		system("pause");
		exit(0);
	}
	vector<aitVertex> verts = mesh.getVertices();
	NUMVERTS = verts.size();

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aitVertex) * NUMVERTS, &verts[0], GL_STATIC_DRAW);
	glDrawArrays(GL_POINTS, 0, NUMVERTS);
}*/

/*void GameObject::render(mat4 numParam)
{
	
	glUniformMatrix4fv(GameObject::gModelToWorldTransformLocation, 1, GL_FALSE, &numParam[0][0]);
	glDrawArrays(GL_LINES, 0, GameObject::NUMVERTS);
}*/

string GameObject::getName()
{
	return name;
}
vec3 GameObject::getScale()
{
	return scale;
}
vec3 GameObject::getRotation()
{
	return rotation;
}
vec3 GameObject::getTrans()
{
	return trans;
}
vec3 GameObject::getColor()
{
	return color;
}
