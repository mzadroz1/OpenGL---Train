#include "Cube.h"
#include "ShaderProgram.h"
using namespace std;

GLuint Cube::LoadMipmapTexture(GLuint texId, const char* fname) {
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

void Cube::prepareObject(bool option, const char* fileName) {
	// Build, compile and link shader program
	

	// Set up vertex data 
	GLfloat vertices[32];
	if (option) {
		GLfloat tmp []= {
			// coordinates			// color			// texture
			0.25f,  0.5f,  0.0f,	1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
			-0.75f,  0.5f,  0.0f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,
			-0.25f, -0.5f,  0.0f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
			0.75f, -0.5f,  0.0f,	1.0f, 0.0f, 1.0f,	1.0f,  1.0f
		};
		for (int i = 0; i < 32; i++)
			vertices[i] = tmp[i];
	} else {
		GLfloat tmp[] = {
			// coordinates			// color			// texture
			0.75f,  1.0f,  0.5f,    1.0f, 0.0f, 0.0f,	1.0f,  0.0f,
			-0.25f,  1.0f,  0.5f,	0.0f, 1.0f, 0.0f,	0.0f,  0.0f,
			0.25f, -1.0f,  0.5f,	0.0f, 0.0f, 1.0f,	0.0f,  1.0f,
			1.0f, 0.0f,  0.5f,	    1.0f, 0.0f, 1.0f,	1.0f,  1.0f
		};
		for (int i = 0; i < 32; i++)
			vertices[i] = tmp[i];
	}

	GLuint indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

						  // Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// prepare textures
	texture0 = LoadMipmapTexture(GL_TEXTURE0, fileName);
}

void Cube::draw(GLfloat rot_angle) {

	// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture0);
	glUniform1i(glGetUniformLocation(theProgram->get_programID(), "Texture0"), 0);

	glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0 - rot_angle / 100, 0.0, 0.0));
	trans = glm::rotate(trans, -glm::radians(rot_angle), glm::vec3(0.0, 1.0, 0.0));

	GLuint transformLoc = glGetUniformLocation(theProgram->get_programID(), "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

	// Draw our first triangle
	theProgram->Use();

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
