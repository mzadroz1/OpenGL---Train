#pragma once
#include "Composite.h"
#include "Cube.h"

/*tory
w petli deska(Cube) + 2 kawalki metalu(Cube) 
*/
class Tracks :
	public Composite
{
public:
	Tracks(glm::vec3 coordinates, int tracksAmount, ShaderProgram* shader) {
		for (int i = 0; i < tracksAmount; i++) {
			Object* board = new Cube(coordinates + glm::vec3(0.0f,0.0f,i*2.0f), glm::vec3(2.10f, 0.15f, 0.65f), "oldWood.png", shader);
			items.push_back(board);
			
			Object* track1 = new Cube(coordinates + glm::vec3(0.85f, 0.18f, i * 2.0f), glm::vec3(0.25f, 0.2f, 2.0f), "black-steel.png", shader);
			Object* track2 = new Cube(coordinates + glm::vec3(-0.85f, 0.18f, i * 2.0f), glm::vec3(0.25f, 0.2f, 2.0f), "black-steel.png", shader);
			items.push_back(track1);
			items.push_back(track2);
		}
	}

};

