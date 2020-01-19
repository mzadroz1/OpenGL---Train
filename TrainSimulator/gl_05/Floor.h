#pragma once
#include "Composite.h"
#include "Cube.h"
#include "ShaderProgram.h"

class Floor :
	public Composite
{
public: 
	int const xQunatity = 4;
	int const zQunatity = 10;
	float const partSize = 50.0;
	Floor(glm::vec3 coordinates, ShaderProgram* shader, const char* fileName) {
		/*Cube *floor = new Cube(coordinates, glm::vec3(100, 0.05, 300), fileName, shader);
		items.push_back(floor);*/

		for (int i = 0; i < xQunatity; ++i) {
			for (int j = 0; j < zQunatity; ++j) {
				glm::vec3 partCoordinations = glm::vec3(coordinates.x + i*partSize, coordinates.y, coordinates.z + j*partSize);
				Cube* floorPart = new Cube(partCoordinations, glm::vec3(partSize, 0.05, partSize), fileName, shader);
				items.push_back(floorPart);
			}
		}
		move(glm::vec3(-partSize * xQunatity / 2.0 + partSize*0.5, 0.0, 0.0));
	}
};