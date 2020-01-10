#include "Composite.h"

Composite::~Composite() {
	for (Primitive* item : items) {
		delete item;
	}
}

void Composite::move(glm::vec3 vector) {
	for (Primitive* item : items) {
		item->move(vector);
	}
}

void Composite::scale(glm::vec3 vector) {
	for (Primitive* item : items) {
		item->scale(vector);
	}
}

void Composite::rotate(glm::vec3 vector) {
	for (Primitive* item : items) {
		item->rotate(vector);
	}
}

void Composite::draw() {
	for (Primitive* item : items) {
		item->draw();
	}
}
