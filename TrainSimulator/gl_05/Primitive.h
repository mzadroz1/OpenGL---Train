#pragma once
#include "Object.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <vector>
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
class Primitive :
	public Object
{
	virtual void prepareVertices() = 0;
	virtual void prepareIndices() = 0;
public:
	GLuint VBO, EBO, VAO;
	ShaderProgram* theProgram;
	GLuint texture0;

	glm::vec3 coordinates;
	glm::vec3 rotations;
	glm::vec3 size;
	glm::vec3 colour;

	vector<GLfloat> vertices;
	vector<GLuint> indices;

	Primitive(glm::vec3 coordinates, glm::vec3 rotations, const char* fileName, ShaderProgram* shader, glm::vec3 size = { 1.f, 1.f, 1.f })
		: coordinates(coordinates), rotations(rotations), size(size), theProgram(shader)
	{
	}

	void init(const char* fileName) {
		prepareVertices();
		prepareIndices();
		prepareVAO();
		prepareTexture(fileName);
	}

	


	void prepareVAO() {
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

		// vertex geometry data
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// vertex color data
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// vertex texture coordinates
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

		glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)
	}

	void prepareTexture(const char* fileName) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// prepare textures
		texture0 = LoadMipmapTexture(GL_TEXTURE0, fileName);
	}

	GLuint LoadMipmapTexture(GLuint texId, const char* fname) {
		int width, height;
		unsigned char* image = SOIL_load_image(fname, &width, &height, 0, SOIL_LOAD_RGB);
		if (image == nullptr)
			throw exception("Failed to load texture file");

		GLuint texture;
		glGenTextures(1, &texture);

		glActiveTexture(texId);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		return texture;
	}
	
	void move(glm::vec3 vector) override {
		coordinates += vector;
	}

	void scale(glm::vec3 vector) override {
		size += vector;
	}

	void rotate(glm::vec3 vector) override {
		rotations += vector;
	}

	void draw() override {
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, coordinates);

		trans = glm::rotate(trans, glm::radians(rotations.x), glm::vec3(1.0f, 0.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(rotations.y), glm::vec3(0.0f, 1.0f, 0.0f));
		trans = glm::rotate(trans, glm::radians(rotations.z), glm::vec3(0.0f, 0.0f, 1.0f));

		trans = glm::scale(trans, size);

		theProgram->Use();
		theProgram->setMat4("transform", trans);

		// Bind Textures using texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glUniform1i(glGetUniformLocation(theProgram->get_programID(), "Texture0"), 0);

		

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

};

