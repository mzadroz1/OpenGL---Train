#pragma once
#include "Object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <vector>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
class Primitive :
	public Object
{
	virtual void prepareVertices() = 0;
	virtual void prepareIndices() = 0;
public:
	GLuint VBO, EBO, VAO;
	ShaderProgram* theProgram;
	GLuint texture0;

	glm::vec3 coordinates;
	glm::vec3 rotations;
	glm::vec3 size;

	vector<GLfloat> vertices;
	vector<GLuint> indices;

	Primitive(glm::vec3 coordinates, glm::vec3 rotations, const char* fileName, glm::vec3 size = { 1.f, 1.f, 1.f })
		: coordinates(coordinates), rotations(rotations), size(size) 
	{
	}

	void init(const char* fileName) {
		prepareVertices();
		prepareIndices();
		prepareVAO();
		prepareTexture(fileName);
	}

	


	void prepareVAO();
	void prepareTexture(const char* fileName);
	GLuint LoadMipmapTexture(GLuint texId, const char* fname);
	
	void move(glm::vec3 vector) override;
	void scale(glm::vec3 vector) override;
	void rotate(glm::vec3 vector) override;

	void draw(ShaderProgram* theProgram); //override;

};

