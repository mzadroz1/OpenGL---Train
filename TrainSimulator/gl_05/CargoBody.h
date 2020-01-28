#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "CylindricalPointLight.h"

class CargoBody :
	public Composite
{
public:

	CargoBody(glm::vec3 coordinates, ShaderProgram* shader)
	{
		Object* cabin1 = new Cube(coordinates + glm::vec3(-0.56f, 2.25f, 3.2f), { 0.15f,2.0f,8.25f }, "black-steel.png", shader);
		items.push_back(cabin1);
		Object* cabin2 = new Cube(coordinates + glm::vec3(0.56f, 2.25f, 3.2f), { 0.15f,2.0f,8.25f }, "black-steel.png", shader);
		items.push_back(cabin2);
		Object* cabin3 = new Cube(coordinates + glm::vec3(0, 2.25f, -0.85), { 1.12f,2.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabin3);
		Object* cabin4 = new Cube(coordinates + glm::vec3(0, 2.25f, 7.25f), { 1.1f,2.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabin4);
	}
};

