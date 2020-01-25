#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "CylindricalPointLight.h"

class Car :
	public Composite
{
public:

	Car(glm::vec3 coordinates, ShaderProgram* shader, ShaderProgram* lampShader, const char* bodyTexture)
	{
		Object* body = new Cube(coordinates, { 2.5f,0.6f,1.5f }, bodyTexture, shader);
		items.push_back(body);
		Object* wheel1 = new Cylinder(coordinates - glm::vec3(-0.8f, 0.3f, 0.75f), { 0.3f,0.2f,0.3f }, "textures/car_wheel.png", shader, { 90,0,0 });
		items.push_back(wheel1);
		Object* wheel2 = new Cylinder(coordinates - glm::vec3(0.8f, 0.3f, 0.75f), { 0.3f,0.2f,0.3f }, "textures/car_wheel.png", shader, { 90,0,0 });
		items.push_back(wheel2);
		Object* wheel3 = new Cylinder(coordinates - glm::vec3(-0.8f, 0.3f, -0.75f), { 0.3f,0.2f,0.3f }, "textures/car_wheel.png", shader, { 90,0,0 });
		items.push_back(wheel3);
		Object* wheel4 = new Cylinder(coordinates - glm::vec3(0.8f, 0.3f, -0.75f), { 0.3f,0.2f,0.3f }, "textures/car_wheel.png", shader, { 90,0,0 });
		items.push_back(wheel4);
		Object* glass = new Cube(coordinates - glm::vec3(0.3f, -0.5f, 0.0), { 1.5, 0.5, 1.3 }, "textures/glass.png", shader);
		items.push_back(glass);
		Object* roof = new Cube(coordinates - glm::vec3(0.3f, -0.78f, 0.0), { 1.5, 0.06, 1.3 }, bodyTexture, shader);
		items.push_back(roof);
		Object* post1 = new Cube(coordinates - glm::vec3(-0.43f, -0.5f, 0.63), { 0.06, 0.5, 0.06 }, bodyTexture, shader);
		items.push_back(post1);
		Object* post2 = new Cube(coordinates - glm::vec3(-0.43f, -0.5f, -0.63), { 0.06, 0.5, 0.06 }, bodyTexture, shader);
		items.push_back(post2);
		Object* post3 = new Cube(coordinates - glm::vec3(0.43f, -0.5f, 0.63), { 0.06, 0.5, 0.06 }, bodyTexture, shader);
		items.push_back(post3);
		Object* post4 = new Cube(coordinates - glm::vec3(0.43f, -0.5f, -0.63), { 0.06, 0.5, 0.06 }, bodyTexture, shader);
		items.push_back(post4);
		Object* post5 = new Cube(coordinates - glm::vec3(1.03f, -0.5f, 0.63), { 0.06, 0.5, 0.06 }, bodyTexture, shader);
		items.push_back(post5);
		Object* post6 = new Cube(coordinates - glm::vec3(1.03f, -0.5f, -0.63), { 0.06, 0.5, 0.06 }, bodyTexture, shader);
		items.push_back(post6);
		Object* bmw = new Cylinder(coordinates - glm::vec3(-1.22f, -0.15f, 0.0f), { 0.1f,0.1f,0.1f }, "textures/bmw.png", shader, { 90,0,90 });
		items.push_back(bmw);
		
		Object* lamp_front1 = new CylindricalPointLight(shader, coordinates - glm::vec3(-1.22, 0.0, 0.5), lampShader, { 0.85,0.85,0.55 }, { 0.15,0.15,0.15 });
		lamp_front1->rotate({ 0,0,90 });
		items.push_back(lamp_front1);
		Object* lamp_front2 = new CylindricalPointLight(shader, coordinates - glm::vec3(-1.22, 0.0, -0.5), lampShader, { 0.85,0.85,0.55 }, { 0.15,0.15,0.15 });
		lamp_front2->rotate({ 0,0,90 });
		items.push_back(lamp_front2);
		Object* lamp_back1 = new CylindricalPointLight(shader, coordinates - glm::vec3(1.22, 0.0, 0.5), lampShader, { 1.f, 0.f, 0.f }, { 0.15,0.15,0.15 });
		lamp_back1->rotate({ 0,0,90 });
		items.push_back(lamp_back1);
		Object* lamp_back2 = new CylindricalPointLight(shader, coordinates - glm::vec3(1.22, 0.0, -0.5), lampShader, { 1.f, 0.f, 0.f }, { 0.15,0.15,0.15 });
		lamp_back2->rotate({ 0,0,90 });
		items.push_back(lamp_back2);
		
	}
};