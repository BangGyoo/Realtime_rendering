#ifndef ___SPHERE_H
#define ___SPHERE_H

#include "GL/glew.h"
#include <GL/GL.h>
#include <glm/mat4x4.hpp>

#include <vector>

#include "Loader.h"




class Sphere
{
public:
	Sphere();
	Sphere(float rad, GLuint sl, GLuint st);
	~Sphere();

	void setup();
	void draw();
	int getVertexArrayHandle();

	GLuint vaoHandle, VBO_position, VBO_normal, IBO;

	

private:
	GLuint nVerts, elements;
	float radius;
	GLuint slices, stacks;

	void generateVerts(float *, float *, float *, GLuint *);


};


#endif
