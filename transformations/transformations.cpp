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
#include "Planet.h"
#include "Player.h"
#include "Enemy.h"

# define PI           3.14159265358979323846  /* pi */

using namespace std;
using namespace glm;

const int windowWidth = 1024; 
const int windowHeight = 768;

GLuint VBO;
int NUMVERTS = 3;
float zaxis = 40.0f;
float yaxis = 10.0f;
float xaxis = 0.0f;
static GLuint gModelToWorldTransformLocation;
GLuint gWorldToViewTransformLocation;
GLuint gProjectionTransformLocation;
GLuint gColorLocation;

			//OS,  RS,    OA,    Name,     Scale,                  Rotation,           Translation,             Color,
Planet Sun (0.20f, 0.20f, 90.0f, "Sun", vec3(8.0f, 8.0f, 8.0f), vec3(-1.0, 0.0f, 0.0f), vec3(4.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f));
Planet Earth(0.40f, 0.40f, 0.0f, "Earth", vec3(0.8f, 0.8f, 0.8f), vec3(0.0f, 1, 0.0f), vec3(20.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
Planet Neptune(0.60f, 0.60f, 0.0f, "Neptune", vec3(2.0f, 2.0f, 2.0f), vec3(0.0f, 1, 0.0f), vec3(40.0f, 0.0f, 1.0f), vec3(0.2f, 0.0f, 0.8f));
Planet Jupiter(0.50f, 0.50f, 0.0f, "Jupiter", vec3(3.5f, 3.5f, 3.5f), vec3(0.0f, 1, 0.0f), vec3(29.5f, 0.0f, 1.0f), vec3(1.0f, 0.0f, 0.0f));
Planet EarthMoon(0.40f, 2.0f, 0.0f, "Moon", vec3(0.5f, 0.5f, 0.5f), vec3(0.3f, 1, 0.0f), vec3(1.5f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));
Planet SaturnRings(0.60f, 2.0f, 2.5f, "Rings", vec3(4.0f, 0.0f, 4.0f), vec3(1, 0.0f, 0.0f), vec3(40.0f, 0.0f, 0.0f), vec3(0.5f, 0.5f, 0.5f));

Player Barry(2.0f,"Barry", vec3(0.8f, 0.8f, 0.8f), vec3(0.0f, 1, 0.0f), vec3(5.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
Enemy Chaser(1.0f,vec3(10.0f,0.0f,10.0f),"Enemy", vec3(2.0f,2.0f,2.0f), vec3(0.0f, 1, 0.0f), vec3(20.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 0.0f));



void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int lineAmount = 360; //# of triangles used to draw circle

						  //GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_LINE_LOOP);
	for (i = 0; i <= lineAmount; i++) {
		glVertex2f(
			x + (radius * cos(i *  twicePi / lineAmount)),
			y + (radius* sin(i * twicePi / lineAmount))
		);
	}
	glEnd();
}
void keyPressed(unsigned char key, int x, int y) 
{
	if (key == 'w')
	{
		zaxis -= 1.0f;
		cout << zaxis << endl;
	}
	else if (key == 's')
	{
		zaxis += 1.0f;
		cout << zaxis << endl;
	}
	else if (key == 'a')
	{
		xaxis -= 1.0f;
		cout << xaxis << endl;
	}
	else if (key == 'd')
	{
		xaxis += 1.0f;
		cout << xaxis << endl;
	}
	else if (key == 'q')
	{
		yaxis -= 1.0f;
		cout << yaxis << endl;
	}
	else if (key == 'e')
	{
		yaxis += 1.0f;
		cout << yaxis << endl;
	}
	else if (key == 'n')	
	{ 
		xaxis = 0.0f;
		yaxis = 0.0f;
		zaxis = 20.0f;
	}
	if (key == 'i')
	{
		Barry.setTrans(vec3(0.0f,0.0f,-(Barry.getSpeed())));
	}
	else if (key == 'k')
	{
		Barry.setTrans(vec3(0.0f, 0.0f, Barry.getSpeed()));
	}
	else if (key == 'j')
	{
		Barry.setTrans(vec3(-(Barry.getSpeed()), 0.0f, 0.0f));
	}
	else if (key == 'l')
	{
		Barry.setTrans(vec3(Barry.getSpeed(), 0.0f, 0.0f));
	}
	else if (key == 'o')
	{
		Barry.setTrans(vec3(0.0f, Barry.getSpeed(), 0.0f));
	}
	else if (key == 'u')
	{
		Barry.setTrans(vec3(0.0f, -(Barry.getSpeed()), 0.0f));
	}

}
static void renderSceneCallBack()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Create our world space to view space transformation matrix
	mat4 worldToViewTransform = lookAt(
		vec3(xaxis,yaxis,zaxis), // The position of your camera, in world space
		vec3(0.0f,0.0f,0.0f), // where you want to look at, in world space
		vec3(0.0f,1.0f,0.0f)  // Camera up direction (set to 0,-1,0 to look upside-down)
		); 
	
    // Create out projection transform
    mat4 projectionTransform = perspective(45.0f, (float)windowWidth / (float)windowHeight, 1.0f, 1000.0f);

    // Update the transforms in the shader program on the GPU
    glUniformMatrix4fv(gWorldToViewTransformLocation, 1, GL_FALSE, &worldToViewTransform[0][0]);
    glUniformMatrix4fv(gProjectionTransformLocation, 1, GL_FALSE, &projectionTransform[0][0]);

    glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(aitVertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(aitVertex), (const GLvoid*)12);

	
	
	//Player
	mat4 modelToWorldTransformPlayer = scale(mat4(1.0f), Barry.getScale()) * translate(mat4(1.0f), Barry.getTrans());
	glUniform3f(gColorLocation, Barry.getColor().x, Barry.getColor().y, Barry.getColor().z);
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransformPlayer[0][0]);
	glDrawArrays(GL_LINES, 0, NUMVERTS);

	//Chaser
	vec3 direction = normalize(Barry.getTrans() - Chaser.getDistance());
	Chaser.setDistance(Chaser.getDistance() + direction * 0.05f);
	mat4 modelToWorldTransformEnemy = scale(mat4(1.0f), Chaser.getScale()) * translate(mat4(1.0f), Chaser.getDistance());
	glUniform3f(gColorLocation, Chaser.getColor().x, Chaser.getColor().y , Chaser.getColor().z);
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransformEnemy[0][0]);
	glDrawArrays(GL_LINES, 0, NUMVERTS);
	
	//Sun
	Sun.setRs(0.20f);
	for (float y = 0.0f, s = 8.0f; y < 1.0f, s>1.0f; y += 0.2f, s -= 1.0f)
	{
		Sun.setScale(vec3(s,s,s));
		mat4 modelToWorldTransform1 = scale(mat4(1.0f), Sun.getScale()) * rotate(mat4(1.0f), Sun.getRs(), Earth.getRotation()) * rotate(mat4(1.0f), Sun.getOa(), Sun.getRotation());
			//translate(mat4(1.0f), Sun.getTrans()) ;
		glUniform3f(gColorLocation, 1.0f, y, 0.0f);
		glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform1[0][0]);
		glDrawArrays(GL_LINES, 0, NUMVERTS);
		drawHollowCircle(0.0f, 0.0f, 4.9f);
	}

	//Earth
	Earth.setRs(0.40f);
	
	mat4 modelToWorldTransform2 = rotate(mat4(1.0f), Earth.getRs(), Earth.getRotation()) * translate(mat4(1.0f), Earth.getTrans()) * rotate(mat4(1.0f), Earth.getRs(), Earth.getRotation());
	glUniform3f(gColorLocation, Earth.getColor().x, Earth.getColor().y, Earth.getColor().z);
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform2[0][0]);
	glDrawArrays(GL_LINES, 0, NUMVERTS);
	
	//Neptune
	
	Neptune.setRs(0.60f);
	mat4 modelToWorldTransform3 = rotate(mat4(1.0f), Neptune.getRs(), Neptune.getRotation()) * translate(mat4(1.0f), Neptune.getTrans()) * rotate(mat4(1.0f), Neptune.getRs(), Neptune.getRotation()) * scale(mat4(1.0f), Neptune.getScale());
	glUniform3f(gColorLocation, Neptune.getColor().x, Neptune.getColor().y, Neptune.getColor().z);
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform3[0][0]);
	glDrawArrays(GL_TRIANGLES, 0, NUMVERTS);
	
	//Juptiter
	Jupiter.setRs(0.50f);
	for (float s = 3.5f, r = 0.2f;r<1 , s > 0.0f;r+=0.1f, s -= 0.5f)
	{
		Jupiter.setScale(vec3(s, s, s));
		mat4 modelToWorldTransform4 = rotate(mat4(1.0f), Jupiter.getRs(), Jupiter.getRotation()) * translate(mat4(1.0f), Jupiter.getTrans()) * rotate(mat4(1.0f), Jupiter.getRs(), Jupiter.getRotation()) * scale(mat4(1.0f), Jupiter.getScale());
		glUniform3f(gColorLocation, r, 0.2f, 0.0f);
		glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform4[0][0]);
		glDrawArrays(GL_POINTS, 0, NUMVERTS);
	}

	//Earth Moon
	EarthMoon.setRs(2.0f);
	mat4 modelToWorldTransform5 = rotate(mat4(1.0f), Earth.getRs(), Earth.getRotation()) * translate(mat4(1.0f), Earth.getTrans()) * rotate(mat4(1.0f), EarthMoon.getRs(), EarthMoon.getRotation()) * translate(mat4(1.0f), EarthMoon.getTrans()) * rotate(mat4(1.0f), Earth.getRs(), Earth.getRotation()) * scale(mat4(1.0f), EarthMoon.getScale());
	glUniform3f(gColorLocation, EarthMoon.getColor().x, EarthMoon.getColor().y, EarthMoon.getColor().z);
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform5[0][0]);
	glDrawArrays(GL_LINES, 0, NUMVERTS);
	
	//Saturn Rings
	SaturnRings.setRs(2.0f);
	mat4 modelToWorldTransform6 = rotate(mat4(1.0f), Neptune.getRs(), Neptune.getRotation()) * translate(mat4(1.0f), Neptune.getTrans()) * rotate(mat4(1.0f), SaturnRings.getRs(), Earth.getRotation()) * rotate(mat4(1.0f), SaturnRings.getOa(), SaturnRings.getRotation()) * scale(mat4(1.0f), SaturnRings.getScale());
	glUniform3f(gColorLocation, SaturnRings.getColor().x, SaturnRings.getColor().y, SaturnRings.getColor().z);
	glUniformMatrix4fv(gModelToWorldTransformLocation, 1, GL_FALSE, &modelToWorldTransform6[0][0]);
	glDrawArrays(GL_POINTS, 0, NUMVERTS);
	
    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

    glutSwapBuffers();
}

static void initializeGlutCallbacks()
{
    glutDisplayFunc(renderSceneCallBack);
    glutIdleFunc(renderSceneCallBack);
}

static void createVertexBuffer()
{
	
	aitMesh mesh;
	if (!mesh.loadFromObj("assets/sphere.obj"))
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
}
/*void GameObject::createVertexBuffer(string path)
{
	path = "sphere";
}*/



static void addShader(GLuint shaderProgram, const char* pShaderText, GLenum shaderType)
{
    GLuint shaderObj = glCreateShader(shaderType);

	if (shaderObj == 0) 
	{
		std::stringstream ss;
		ss<<"Error creating shader type "<<shaderType<<endl;
		AIT_ASSERT(0, ss.str());
    }

    const GLchar* p[1];
    p[0] = pShaderText;
    GLint Lengths[1];
    Lengths[0]= strlen(pShaderText);
    glShaderSource(shaderObj, 1, p, Lengths);
    glCompileShader(shaderObj);
    GLint success;
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
    if (!success) 
	{
        GLchar InfoLog[1024];
        glGetShaderInfoLog(shaderObj, 1024, NULL, InfoLog);
		std::stringstream ss;
		ss <<"Error compiling shader type "<<shaderType<<": "<<InfoLog<<endl;
		AIT_ASSERT(0, ss.str());
    }

    glAttachShader(shaderProgram, shaderObj);
}

const string readFileToString(char* filename)
{
	ifstream file (filename, ios::in);
	if (file.is_open())
	{
        stringstream continut;
        continut << file.rdbuf();
        continut << '\0';
		return continut.str();
	}
    return "";
}

static void buildShaders()
{
    GLuint shaderProgram = glCreateProgram();

    if (shaderProgram == 0) 
	{
		AIT_ASSERT(0, "Error creating shader program\n");
    }

	string VS = readFileToString("vertexShader.glsl");
	string FS = readFileToString("fragmentShader.glsl");

	addShader(shaderProgram, VS.c_str(), GL_VERTEX_SHADER);
	addShader(shaderProgram, FS.c_str(), GL_FRAGMENT_SHADER);

    GLint success = 0;
    GLchar errorLog[1024] = { 0 };

    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
 	if (success == 0) 
	{
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		std::stringstream ss;
		ss<<"Error linking shader program: "<<errorLog<<endl;
		AIT_ASSERT(0, ss.str());
	}

    glValidateProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &success);
    if (!success) 
	{
        glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
        cerr<<"Error linking shader program: "<<errorLog<<endl;
        std::stringstream ss;
		ss<<"Error linking shader program: "<<errorLog<<endl;
		AIT_ASSERT(0, ss.str());
    }

    glUseProgram(shaderProgram);

    gModelToWorldTransformLocation = glGetUniformLocation(shaderProgram, "gModelToWorldTransform");
    assert(gModelToWorldTransformLocation != 0xFFFFFFFF);
    gWorldToViewTransformLocation = glGetUniformLocation(shaderProgram, "gWorldToViewTransform");
    assert(gWorldToViewTransformLocation != 0xFFFFFFFF);
    gProjectionTransformLocation = glGetUniformLocation(shaderProgram, "gProjectionTransform"); 
    assert(gProjectionTransformLocation != 0xFFFFFFFF);
    
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Solar System");

    initializeGlutCallbacks();

    // Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK) 
    {
		cerr<<"Error: "<<glewGetErrorString(res)<<"\n";
		return 1;
    }

	buildShaders();
	// Enable the z-buffer
	glEnable(GL_DEPTH_TEST);
	// GL_LESS - Passes if the incoming depth value is less than the stored depth value
	glDepthFunc(GL_LESS);

	//Enable backface culling
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); 
	glutKeyboardFunc(keyPressed);
	// Create a vertex buffer
	//Earth->createVertexBuffer();
	createVertexBuffer();
	
	

    glutMainLoop();
    
    return 0;
}