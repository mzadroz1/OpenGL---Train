#pragma once
#include "Composite.h"
#include "Cylinder.h"
#include "SphericalPointLight.h"

/*Street Lamp
noga (waski wysoki Cylinder) + lampa (szeroki niski Cylinder / Sphere)
*/
class StreetLamp :
	public Composite
{
public:
	StreetLamp(glm::vec3 coordinates, ShaderProgram *shader, ShaderProgram *lampShader, glm::vec3 color = { 0.95f,0.95f,0.65f })
	{
		Object* post = new Cylinder(coordinates + glm::vec3(0.0f, 2.5f, 0.0f), glm::vec3(0.15f, 5.0f, 0.15f), "steel.png", shader);
		items.push_back(post);
		Object* hat = new Cylinder(coordinates + glm::vec3(-0.45f, 5.3f, 0.0f), { 0.65f,0.15f,0.25f }, "steel.png", shader, { 0,0,-30 });
		items.push_back(hat);
		Object* lamp = new SphericalPointLight(shader, coordinates + glm::vec3(-0.58f, 5.25f, 0.0f), lampShader,color,{0.5f,0.15f,0.22f});
		lamp->rotate(glm::vec3(0, 0, -30));
		items.push_back(lamp);
		
	}
};

