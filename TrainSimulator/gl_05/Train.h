#pragma once
#include "Composite.h"
#include "TrainChassis.h"
#include "TrainBody.h"

/*Train
TrainChassis + TrainBody*/
class Train :
	public Composite
{
public:
	Train(glm::vec3 coordinates, ShaderProgram* shader, ShaderProgram* lampShader)
	{
		Object* chassis = new TrainChassis(coordinates, shader);
		Object* body = new TrainBody(coordinates, shader, lampShader);
		items.push_back(chassis);
		items.push_back(body);
	}
};

