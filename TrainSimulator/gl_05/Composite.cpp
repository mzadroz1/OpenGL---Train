#include "Composite.h"

Composite::~Composite() {
	for (Object* item : items) {
		delete item;
	}
}

void Composite::move(glm::vec3 vector) {
	for (Object* item : items) {
		item->move(vector);
	}
}

void Composite::scale(glm::vec3 vector) {
	for (Object* item : items) {
		item->scale(vector);
	}
}

void Composite::rotate(glm::vec3 vector) {
	for (Object* item : items) {
		item->rotate(vector);
	}
}

void Composite::draw() {
	for (Object* item : items) {
		item->draw();
	}
}
