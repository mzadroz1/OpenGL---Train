#pragma once
#include "Composite.h"
#include "Cube.h"

class Road :
	public Composite
{
public:
	Road(glm::vec3 coordinates, int tracksAmount, ShaderProgram* shader) {
		for (int i = 0; i < tracksAmount; i++) {
			Object* road = new Cube(coordinates + glm::vec3(i * 20.0f, 0.0f, 0.0f), glm::vec3(20.0f, 0.1f, 5.0f), "textures/asphalt1.png", shader);
			items.push_back(road);
		}
	}

};
