#pragma once
#include "Composite.h"
#include "CargoChassis.h"
#include "CargoBody.h"

class Cargo :
	public Composite
{
public:
	Cargo(glm::vec3 coordinates, int numberOfCargos, ShaderProgram* shader)
	{
		Object* chassis;
		Object* body;

		chassis = new CargoChassis(coordinates + glm::vec3(0.f, 0.f, 0.f), shader);
		body = new CargoBody(coordinates + glm::vec3(0.f, 0.f, 0.f), shader);

		items.push_back(body);
		items.push_back(chassis);

		for (int i = 1; i < numberOfCargos; i++) {
			chassis = new CargoChassis(coordinates + glm::vec3(0.f, 0.f, -8.75f * i), shader);
			body = new CargoBody(coordinates + glm::vec3(0.f, 0.f, -8.75f *i), shader);

			items.push_back(body);
			items.push_back(chassis);
		}

	}
};

