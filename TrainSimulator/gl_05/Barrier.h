#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "Cube.h"

class Barrier :
	public Composite
{
public:

	Barrier(glm::vec3 coordinates, ShaderProgram* shader)
	{
		Object* leg = new Cube(coordinates, { 0.4f,0.9f,0.4f }, "metal.png",shader);
		items.push_back(leg);
		Object* barrier = new Cylinder(coordinates - glm::vec3(0.0f, -0.35f, 1.5f), { 0.1f,3.0f,0.1f }, "textures/barrier.png", shader, { 90,0,0 });
		items.push_back(barrier);

	}
};
