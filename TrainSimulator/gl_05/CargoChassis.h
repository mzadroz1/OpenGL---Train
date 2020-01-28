#pragma once
#include "Composite.h"
#include "Cylinder.h"

class CargoChassis :
	public Composite
{
public:
	CargoChassis(glm::vec3 coordinates, ShaderProgram* shader)
	{
		Object* wheel1 = new Cylinder(coordinates - glm::vec3(0.85f, -0.93f, 0.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel1);
		Object* wheel2 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.93f, 0.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel2);
		Object* wheel3 = new Cylinder(coordinates - glm::vec3(0.85f, -0.93f, -2.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel3);
		Object* wheel4 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.93f, -2.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel4);

		Object* wheel5 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.93f, -4.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel5);
		Object* wheel6 = new Cylinder(coordinates - glm::vec3(0.85f, -0.93f, -4.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel6);
		Object* wheel7 = new Cylinder(coordinates - glm::vec3(-0.85f, -0.93f, -6.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel7);
		Object* wheel8 = new Cylinder(coordinates - glm::vec3(0.85f, -0.93f, -6.0f), { 0.65f,0.25f,0.65f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(wheel8);

		Object* rod1 = new Cube(coordinates + glm::vec3(1.0f, 0.70f, 0.88f), { 0.15f,0.15f,2.0f }, "metal.png", shader, { 0,0,0 });
		items.push_back(rod1);
		Object* rod2 = new Cube(coordinates + glm::vec3(-1.0f, 0.70f, 0.88f), { 0.15f,0.15f,2.0f }, "metal.png", shader, { 0,0,0 });
		items.push_back(rod2);
		Object* rodWheel1 = new Cylinder(coordinates + glm::vec3(1.1f, 0.70f, 1.9f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel1);
		Object* rodWheel2 = new Cylinder(coordinates + glm::vec3(-1.1f, 0.70f, 1.9f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel2);
		Object* rodWheel3 = new Cylinder(coordinates + glm::vec3(1.1f, 0.70f, -0.1f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel3);
		Object* rodWheel4 = new Cylinder(coordinates + glm::vec3(-1.1f, 0.70f, -0.1f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel4);

		//poprawiæ belki i ma³e coœki

		Object* rod3 = new Cube(coordinates + glm::vec3(1.0f, 0.70f, 2.9f), { 0.15f,0.15f,2.0f }, "metal.png", shader, { 0,0,0 });
		items.push_back(rod3);
		Object* rod4 = new Cube(coordinates + glm::vec3(-1.0f, 0.70f, 2.9f), { 0.15f,0.15f,2.0f }, "metal.png", shader, { 0,0,0 });
		items.push_back(rod4);
		Object* rod5 = new Cube(coordinates + glm::vec3(1.0f, 0.70f, 4.8f), { 0.15f,0.15f,2.0f }, "metal.png", shader, { 0,0,0 });
		items.push_back(rod5);
		Object* rod6 = new Cube(coordinates + glm::vec3(-1.0f, 0.70f, 4.8f), { 0.15f,0.15f,2.0f }, "metal.png", shader, { 0,0,0 });
		items.push_back(rod6);
		Object* rodWheel5 = new Cylinder(coordinates + glm::vec3(1.1f, 0.70f, 3.9f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel5);
		Object* rodWheel6 = new Cylinder(coordinates + glm::vec3(-1.1f, 0.70f, 3.9f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel6);
		Object* rodWheel7 = new Cylinder(coordinates + glm::vec3(1.1f, 0.70f, 5.9f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel7);
		Object* rodWheel8 = new Cylinder(coordinates + glm::vec3(-1.1f, 0.70f, 5.9f), { 0.15f,0.15f,0.15f }, "wheel.png", shader, { 0,0,90 });
		items.push_back(rodWheel8);

		Object* rod7 = new Cube(coordinates + glm::vec3(0.f, 1.13f, 7.75f), {0.25f, 0.3f, 0.5f}, "black-steel.png", shader);
		items.push_back(rod7);
		//przesun¹æ do przodu

		Object* deck = new Cube(coordinates + glm::vec3(0.0f, 1.13f, 3.25f), { 1.45f,0.3f,8.5f }, "black-steel.png", shader);
		items.push_back(deck);
		for (int i = 0; i < 8; i++)
		{
			items[i]->rotate({ 65,0,0 });
		}
	}

	float dx0 = -0.12f, dy0 = -0.23f, pos = -190.0f;

	void move(glm::vec3 vector) override
	{
		Composite::move(vector);
		float angle = vector.z * 180 / M_PI / 0.65f;
		for (int i = 0; i < 8; i++)
		{
			items[i]->rotate({ angle,0,0 });
		}
		float dx = 0.259422 * cos(pos / 180 * M_PI);
		float dy = 0.259422 * sin(pos / 180 * M_PI);

		for (int i = 8; i < 22; i++)
		{
			items[i]->move({ 0,-dy0 + dy,-dx0 + dx });
		}
		pos -= angle;
		dx0 = dx;
		dy0 = dy;

	}
};


