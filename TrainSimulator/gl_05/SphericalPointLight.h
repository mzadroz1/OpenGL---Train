#pragma once
#include "BlockPointLight.h"
#include "Sphere.h"

class SphericalPointLight :
	public BlockPointLight {
public:
	SphericalPointLight(ShaderProgram* _shader, glm::vec3 _lightPos,
		ShaderProgram* _blockShader, glm::vec3 _diffuse = { 0.5f, 0.5f, 0.5f }, glm::vec3 _blockSize = { 0.25f, 0.25f, 0.25f },
		glm::vec3 _ambient = { 0.2f, 0.2f, 0.2f }, glm::vec3 _specular = { 0.2f, 0.2f, 0.2f },
		float _constant = 1.0f, float _linear = 0.09f, float _quadratic = 0.032f):
		BlockPointLight(_shader, _lightPos, _diffuse, _ambient, _specular, _constant, _linear, _quadratic) {
		block = new Sphere(_lightPos, _blockSize, "moon1024.bmp", _blockShader);
	}
};