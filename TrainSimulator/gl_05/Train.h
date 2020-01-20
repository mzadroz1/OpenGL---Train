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
	TrainChassis* chassis;
	TrainBody* body;
	Train(glm::vec3 coordinates, ShaderProgram* shader, ShaderProgram* lampShader)
	{
		chassis = new TrainChassis(coordinates, shader);
		body = new TrainBody(coordinates, shader, lampShader);
		items.push_back(chassis);
		items.push_back(body);
	}

	void setLightsBrightness(float brightness) {
		for (BlockPointLight* lamp : body->lamps) {
			if (lamp->diffuse.x + brightness >= 0.0 && lamp->diffuse.x + brightness <= 1.0
			&& lamp->diffuse.y + brightness >= 0.0 && lamp->diffuse.y + brightness <= 1.0
			&& lamp->diffuse.z + brightness >= 0.0 && lamp->diffuse.z + brightness <= 1.0) 
			{
				lamp->changeColour(glm::vec3(lamp->diffuse.x + brightness, lamp->diffuse.y + brightness, lamp->diffuse.z + brightness));
			}
		}
	}
};

