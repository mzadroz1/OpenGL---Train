#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "SphericalPointLight.h"


class Semaphore :
	public Composite
{
private:


public:
	Semaphore(glm::vec3 coordinates, ShaderProgram* shader, ShaderProgram* lampShader)
	{
		Object* stick = new Cylinder(coordinates + glm::vec3(0.f, 2.5f, 0.f), glm::vec3(0.1f, 5.0f, 0.1f), "steel.png", shader);
		items.push_back(stick);
		Object* box = new Cube(coordinates + glm::vec3(0.0f, 4.8f, 0.0f), { 0.5f,1.6f,0.5f }, "steel.png", shader);
		items.push_back(box);
		Object* hat1 = new Sphere(coordinates + glm::vec3(0.f, 4.5f, 0.25f), glm::vec3(0.25f, 0.05f, 0.4f), "moon1024.bmp", shader);
		items.push_back(hat1);
		Object* hat2 = new Sphere(coordinates + glm::vec3(0.f, 5.f, 0.25f), glm::vec3(0.25f, 0.05f, 0.4f), "moon1024.bmp", shader);
		items.push_back(hat2);
		Object* hat3 = new Sphere(coordinates + glm::vec3(0.f, 5.5f, 0.25f), glm::vec3(0.25f, 0.05f, 0.4f), "moon1024.bmp", shader);
		items.push_back(hat3);

		SphericalPointLight* lampGreen = new SphericalPointLight(shader, coordinates + glm::vec3(0.f, 4.25f, 0.25f), lampShader, {0.3f, 0.3f, 0.3f}, glm::vec3(0.15f, 0.15f, 0.15f));
		SphericalPointLight* lampYellow = new SphericalPointLight(shader, coordinates + glm::vec3(0.f, 4.75f, 0.25f), lampShader, { 0.3f, 0.3f, 0.3f }, glm::vec3(0.15f, 0.15f, 0.15f));
		SphericalPointLight* lampRed = new SphericalPointLight(shader, coordinates + glm::vec3(0.f, 5.25f, 0.25f), lampShader, { 1.f, 0.f, 0.f }, glm::vec3(0.15f, 0.15f, 0.15f));

		items.push_back(lampRed);
		items.push_back(lampYellow);
		items.push_back(lampGreen);
		
	}

	void changeToGreen() {
		((SphericalPointLight *)items[5])->changeColour({ 0.3f, 0.3f, 0.3f });
		((SphericalPointLight*)items[6])->changeColour({ 0.3f, 0.3f, 0.3f });
		((SphericalPointLight*)items[7])->changeColour({ 0.f, 1.f, 0.f });
	}

	void changeToRed() {
		((SphericalPointLight*)items[5])->changeColour({ 1.f, 0.f, 0.f });
		((SphericalPointLight*)items[6])->changeColour({ 0.3f, 0.3f, 0.3f });
		((SphericalPointLight*)items[7])->changeColour({ 0.3f, 0.3f, 0.3f });
	}

	void changeToYellow() {
		((SphericalPointLight*)items[5])->changeColour({ 0.3f, 0.3f, 0.3f });
		((SphericalPointLight*)items[6])->changeColour({ 1.f, 1.f, 0.0f });
		((SphericalPointLight*)items[7])->changeColour({ 0.3f, 0.3f, 0.3f });
	}

	void changeToYellowRed() {
		((SphericalPointLight*)items[5])->changeColour({ 1.f, 0.f, 0.f });
		((SphericalPointLight*)items[6])->changeColour({ 1.f, 1.f, 0.0f });
		((SphericalPointLight*)items[7])->changeColour({ 0.3f, 0.3f, 0.3f });
	}
};

