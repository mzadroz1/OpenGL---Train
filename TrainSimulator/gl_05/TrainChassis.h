#pragma once
#include "Composite.h"
#include "Cylinder.h"

/*Train Chassis - podwozie
4 kola (Cylider) + 2 latajace laczniki (Cube)
*/
class TrainChassis :
	public Composite
{
public:
	TrainChassis(glm::vec3 coordinates, ShaderProgram* shader)
	{
		Object* wheel1 = new Cylinder(coordinates - glm::vec3(0.85f, -0.93f, 0.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90});
		items.push_back(wheel1);
		Object* wheel2 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.93f, 0.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel2);
		Object* wheel3 = new Cylinder(coordinates - glm::vec3(0.85f, -0.93f, -2.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel3);
		Object* wheel4 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.93f, -2.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel4);
		
		Object* wheel5 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.63f, -4.0f), { 0.35f,0.25f,0.35f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel5);
		Object* wheel6 = new Cylinder(coordinates - glm::vec3(0.85f, -0.63f, -4.0f), { 0.35f,0.25f,0.35f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel6);
		Object* wheel7 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.63f, -5.0f), { 0.35f,0.25f,0.35f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel7);
		Object* wheel8 = new Cylinder(coordinates - glm::vec3(0.85f, -0.63f, -5.0f), { 0.35f,0.25f,0.35f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel8);

		Object* wheelBar1 = new Cube(coordinates + glm::vec3(0.0f, 0.63f, 5.0f), { 1.55f,0.15f,0.15f }, "black-steel.png", shader, { 0,0,0 });
		items.push_back(wheelBar1);
		Object* wheelBar2 = new Cube(coordinates + glm::vec3(0.0f, 0.63f, 4.0f), { 1.55f,0.15f,0.15f }, "black-steel.png", shader, { 0,0,0 });
		items.push_back(wheelBar2);
		Object* wheelBar3 = new Cube(coordinates + glm::vec3(0.0f, 0.83f, 5.0f), { 0.55f,0.15f,0.15f }, "black-steel.png", shader, { 0,0,90 });
		items.push_back(wheelBar3);
		Object* wheelBar4 = new Cube(coordinates + glm::vec3(0.0f, 0.83f, 4.0f), { 0.55f,0.15f,0.15f }, "black-steel.png", shader, { 0,0,90 });
		items.push_back(wheelBar4);

		Object* bar1 = new Cube(coordinates + glm::vec3(-0.75f, 0.7f, 5.55f), {1.0f,0.15f,0.15f}, "metal.png", shader,{0,0,75});
		items.push_back(bar1);
		Object* bar2 = new Cube(coordinates + glm::vec3(0.75f, 0.7f, 5.55f), { 1.0f,0.15f,0.15f }, "metal.png", shader, { 0,0,-75 });
		items.push_back(bar2);
		Object* bar3 = new Cube(coordinates + glm::vec3(0.0f, 1.13f, 5.56f), { 1.35f,0.15f,0.15f }, "metal.png", shader, { 0,0,0 });
		items.push_back(bar3);

		Object* bar4 = new Cube(coordinates + glm::vec3(-0.4f, 0.35f, 6.0f), { 1.25f,0.15f,0.15f }, "metal.png", shader, { 0,-45,0 });
		items.push_back(bar4);
		Object* bar5 = new Cube(coordinates + glm::vec3(0.4f, 0.35f, 6.0f), { 1.25f,0.15f,0.15f }, "metal.png", shader, { 0,45,0 });
		items.push_back(bar5);

		Object* bar6 = new Cube(coordinates + glm::vec3(0.0f, 0.7f, 6.0f), { 1.07f,0.15f,0.15f }, "metal.png", shader, { -45,0,90 });
		items.push_back(bar6);

		Object* bar7 = new Cube(coordinates + glm::vec3(-0.425f, 0.7f, 5.68f), { 0.9f,0.15f,0.15f }, "metal.png", shader, { -20,0,-105 });
		items.push_back(bar7);
		Object* bar8 = new Cube(coordinates + glm::vec3(0.425f, 0.7f, 5.68f), { 0.9f,0.15f,0.15f }, "metal.png", shader, { -20,0,105 });
		items.push_back(bar8);
		
		Object* deck = new Cube(coordinates + glm::vec3(0.0f, 1.13f, 2.25f), { 1.45f,0.3f,6.5f }, "black-steel.png", shader);
		items.push_back(deck);
	}
};

