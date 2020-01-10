#pragma once
#include "Object.h"
#include "Primitive.h"
#include <vector>

using namespace std;
class Composite :
	public Object
{
	vector<Primitive*> items;
	long itemsQuantity;
public:
	~Composite();

	void move(glm::vec3 vector) override;
	void scale(glm::vec3 vector) override;
	void rotate(glm::vec3 vector) override;

	void draw() override;
};

