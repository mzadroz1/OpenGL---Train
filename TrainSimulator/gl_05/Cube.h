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
#include "Primitive.h"
class Cube : public Primitive
{
public: 
	Cube(glm::vec3 coordinates, glm::vec3 size, const char* fileName, ShaderProgram * shader,
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f)) :
		Primitive(coordinates, rotation, fileName, shader, size)
	{
		init(fileName);
	}

	void prepareVertices() override;
	void prepareIndices() override;


};

