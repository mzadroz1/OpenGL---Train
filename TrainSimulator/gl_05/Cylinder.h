#pragma once
#include "Primitive.h"
class Cylinder : public Primitive
{
public: 
	Cylinder(glm::vec3 coordinates, glm::vec3 size, const char* fileName, ShaderProgram* shader,
		glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f)) :
		Primitive(coordinates, rotation, fileName, shader, size) 
	{
		init(fileName);
	}


	void prepareVertices() override;
	void prepareIndices() override;
};

