#pragma once

#include <glm/glm.hpp>
//#include "ShaderProgram.h"

class Object
{
public:
	//virtual void draw(ShaderProgram* theProgram) = 0;
	virtual void move(glm::vec3 vector) = 0;
	virtual void scale(glm::vec3 vector) = 0;
	virtual void rotate(glm::vec3 vector) = 0;

};

