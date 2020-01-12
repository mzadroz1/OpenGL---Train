#pragma once
#include "Cube.h"
class PointLight
{
public:
	Cube* lamp;
	ShaderProgram* theProgram;
	ShaderProgram* lampShader;

	PointLight(Cube* lamp, ShaderProgram* theProgram) {
		this->lamp = lamp;
		this->theProgram = theProgram;
		theProgram->setVec3("light.position", lamp->coordinates);
		

		// light properties
		theProgram->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		theProgram->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		theProgram->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
	}

};

