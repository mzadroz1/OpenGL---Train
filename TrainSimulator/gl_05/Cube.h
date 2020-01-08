#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
class Cube
{
public: 
	GLuint VBO, EBO, VAO;
	ShaderProgram* theProgram;
	GLuint texture0;


	Cube(){
		theProgram = new ShaderProgram("gl_05.vert", "gl_05.frag");
	};

	~Cube() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	};

	GLuint LoadMipmapTexture(GLuint texId, const char* fname);

	void prepareObject(bool option, const char* fileName);

	void draw(GLfloat rot_angle);
};

