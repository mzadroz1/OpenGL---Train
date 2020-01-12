#pragma once
#include "Object.h"
#include "PointLight.h"
#include "Cube.h"
class CubicPointLight : 
	public PointLight, 
	public Object {
public:
	Cube* cube;

	CubicPointLight(ShaderProgram* _shader, glm::vec3 _lightPos,
		ShaderProgram* _cubeShader, glm::vec3 _diffuse = { 0.5f, 0.5f, 0.5f }, glm::vec3 _cubeSize = { 0.25f, 0.25f, 0.25f },
		glm::vec3 _ambient = { 0.2f, 0.2f, 0.2f }, glm::vec3 _specular = { 1.0f, 1.0f, 1.0f },
		float _constant = 1.0f, float _linear = 0.09f, float _quadratic = 0.032f):
		PointLight(_shader, _lightPos, _ambient, _diffuse, _specular, _constant, _linear, _quadratic)	{
		cube = new Cube(_lightPos, _cubeSize, "iipw.png", _cubeShader);
	
	}

	~CubicPointLight() {
		delete cube;
	}

	void draw() {
		cube->theProgram->Use();
		cube->theProgram->setVec3("colour", diffuse);
		cube->draw();
	}

	void move(glm::vec3 vector) {
		PointLight::move(vector);
		cube->move(vector);
	}

	void scale(glm::vec3 vector) {
		cube->scale(vector);
	}

	void rotate(glm::vec3 vector) {
		cube->rotate(vector);
	}

};