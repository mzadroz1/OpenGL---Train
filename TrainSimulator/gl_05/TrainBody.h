#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "CylindricalPointLight.h"

/*Train Body - nadwozie
kabina(Cube) + silnik(Cylinder) + komin(Cylinder) + dach(Cube) + podloga(Cube)
*/
class TrainBody :
	public Composite
{
public:
	TrainBody(glm::vec3 coordinates, ShaderProgram * shader, ShaderProgram* lampShader)
	{
		Object* body = new Cylinder(coordinates + glm::vec3(0.0f, 2.0f, 3.53f), { 0.7f,3.4f,0.7f }, "locoBody.png", shader, { 90,0,0 });
		items.push_back(body);
		Object* elka = new Cylinder(coordinates + glm::vec3(0.0f, 2.0f, 5.25f), { 0.5f,0.25f,0.5f }, "elka.png", shader, { 90,0,0 });
		items.push_back(elka);

		Object* cabinBar1 = new Cylinder(coordinates + glm::vec3(-0.56f, 2.75f, -0.85f), { 0.15f,3.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabinBar1);
		Object* cabinBar2 = new Cylinder(coordinates + glm::vec3(0.56f, 2.75f, -0.85f), { 0.15f,3.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabinBar2);
		Object* cabinBar3 = new Cylinder(coordinates + glm::vec3(-0.56f, 2.75f, 2.0f), { 0.15f,3.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabinBar3);
		Object* cabinBar4 = new Cylinder(coordinates + glm::vec3(0.56f, 2.75f, 2.0f), { 0.15f,3.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabinBar4);

		Object* cabin1 = new Cube(coordinates + glm::vec3(-0.56f, 2.25f, 0.575f), { 0.15f,2.0f,2.85f }, "black-steel.png", shader);
		items.push_back(cabin1);
		Object* cabin2 = new Cube(coordinates + glm::vec3(0.56f, 2.25f, 0.575f), { 0.15f,2.0f,2.85f }, "black-steel.png", shader);
		items.push_back(cabin2);
		Object* cabin3 = new Cube(coordinates + glm::vec3(0, 2.25f, -0.85), { 1.12f,2.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabin3);
		Object* cabin4 = new Cube(coordinates + glm::vec3(0, 2.25f, 2.0f), { 1.12f,2.0f,0.15f }, "black-steel.png", shader);
		items.push_back(cabin4);

		Object * roof = new Cube(coordinates + glm::vec3(0, 4.5f, 0.575), { 1.75f,0.5f,4.0f }, "black-steel.png", shader);
		items.push_back(roof);
		
		Object* chimney1 = new Cylinder(coordinates + glm::vec3(0.0f, 3.1f, 4.0f), { 0.25f,1.0f,0.25f }, "black-steel.png",shader);
		items.push_back(chimney1);
		Object* chimney2 = new Cylinder(coordinates + glm::vec3(0.0f, 3.7f, 4.0f), { 0.35f,0.25f,0.35f }, "black-steel.png", shader);
		items.push_back(chimney2);

		

		Object* lamp1 = new CylindricalPointLight(shader, coordinates + glm::vec3(0.5f, 1.5f, 5.33f), lampShader,{0.85,0.85,0.55},{0.15,0.15,0.15});
		lamp1->rotate({ 90,0,0 });
		items.push_back(lamp1);
		Object* cloche1 = new Cylinder(coordinates + glm::vec3(0.5f, 1.5f, 5.305f), { 0.20,0.15,0.20 },"black-steel.png", shader ,{90,0,0});
		items.push_back(cloche1);
		
		Object* lamp2 = new CylindricalPointLight(shader, coordinates + glm::vec3(-0.5f, 1.5f, 5.33f), lampShader, { 0.85,0.85,0.55 }, { 0.15,0.15,0.15 });
		lamp2->rotate({ 90,0,0 });
		items.push_back(lamp2);
		Object* cloche2 = new Cylinder(coordinates + glm::vec3(-0.5f, 1.5f, 5.305f), { 0.20,0.15,0.20 }, "black-steel.png", shader, { 90,0,0 });
		items.push_back(cloche2);
	}
};

