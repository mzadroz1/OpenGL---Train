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
		Object* body = new Cylinder(coordinates + glm::vec3(0.0f, 2.0f, 2.10f), { 0.7f,6.25f,0.7f }, "black-steel.png", shader, { 90,0,0 });
		items.push_back(body);

		Object* lamp1 = new CylindricalPointLight(shader, coordinates + glm::vec3(0.5f, 1.5f, 5.33f), lampShader,{0.85,0.85,0.55},{0.2,0.2,0.2});
		lamp1->rotate({ 90,0,0 });
		items.push_back(lamp1);
		Object* lamp2 = new CylindricalPointLight(shader, coordinates + glm::vec3(-0.5f, 1.5f, 5.33f), lampShader, { 0.85,0.85,0.55 }, { 0.2,0.2,0.2 });
		lamp2->rotate({ 90,0,0 });
		items.push_back(lamp2);
	}
};

