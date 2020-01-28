#pragma once
#include "Composite.h"
#include "CargoChassis.h"

class Cargo :
	public Composite
{
public:
	CargoChassis* chassis;
	Cargo(glm::vec3 coordinates, ShaderProgram* shader)
	{
		chassis = new CargoChassis(coordinates, shader);


		items.push_back(chassis);
	}
};

