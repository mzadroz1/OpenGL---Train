#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include "StreetLamp.h"
using namespace std;
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"
#include "Primitive.h"
#include "Cube.h"
#include "Camera.h"
#include "PointLight.h"
#include "Cylinder.h"
#include "CubicPointLight.h"
#include "Tracks.h"
#include "Sphere.h"
#include "SphericalPointLight.h"
#include "CylindricalPointLight.h"

const float MAX_FPS = 60.0f;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


int PointLight::pointLightsQuantity = 0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

GLuint LoadMipmapTexture(GLuint texId, const char* fname)
{
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
Camera camera(glm::vec3(-1.0f, 2.0f, 10.0f));
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{

	if (glfwInit() != GL_TRUE)
	{
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try
	{
		const GLuint WIDTH = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
		const GLuint HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

		GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "GKOM - OpenGL 05", nullptr, nullptr);
		if (window == nullptr)
			throw exception("GLFW window not created");
		glfwMakeContextCurrent(window);

		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
			throw exception("GLEW Initialization failed");

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);

		// tell GLFW to capture our mouse
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glEnable(GL_DEPTH_TEST);

		glViewport(0, 0, WIDTH, HEIGHT);

		ShaderProgram ourShader("gl_05.vert", "gl_05.frag");
		ShaderProgram lampShader("LampShader.vert", "LampShader.frag");
		
		Cube kostka2(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), "iipw.png", &ourShader , glm::vec3(0.0f, 0.0f, 0.0f));
		Cube kostka1(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f), "weiti.png", &ourShader,glm::vec3(0.0f, 0.0f, 0.0f));
		Cube kostka3(glm::vec3(0.5f, -0.5f, 3.0f), glm::vec3(0.5f, 0.5f, 0.5f), "iipw.png", &ourShader,glm::vec3(0.0f, 0.0f, 0.0f));
		Cube kostka4(glm::vec3(-0.5f, -0.5f, 3.0f), glm::vec3(0.5f, 0.5f, 0.5f), "weiti.png", &ourShader,glm::vec3(0.0f, 0.0f, 0.0f));
		Cube prostopadloscian(glm::vec3(0.0f, 0.5f, 1.5f), glm::vec3(1.5f, 1.5f, 3.5f), "iipw.png", &ourShader, glm::vec3(0.0f, 0.0f, 0.0f));


		Cylinder cosiek(glm::vec3(3.f, 3.f, 3.f), glm::vec3(1.f, 2.f, 1.f), "locoBody.png", &ourShader, glm::vec3(90.f, 0.f, 0.f));
		Sphere kulka(glm::vec3(-3.f, -3.f, -3.f), glm::vec3(1.f, 1.f, 1.f), "moon1024.bmp", &ourShader, glm::vec3(-90.f, 0.f, 0.f));
		Sphere kulka2(glm::vec3(-1.f, -1.f, -1.f), glm::vec3(1.f, 1.f, 1.f), "earth2048.bmp", &ourShader, glm::vec3(-90.f, 0.f, 0.f));


		Tracks tory(glm::vec3(0.0f, 0.0f, 0.0f), 50, &ourShader);

		//CubicPointLight cubicLamp1(&ourShader, glm::vec3(0.0f, 2.0f, 1.0f), &lampShader, glm::vec3(1.0f, 0.0f, 0.0f));
		//CubicPointLight cubicLamp2(&ourShader, glm::vec3(1.0f, 2.0f, 1.0f), &lampShader, glm::vec3(0.0f, 0.0f, 1.0f));
		//CubicPointLight cubicLamp3(&ourShader, glm::vec3(-1.0f, 2.0f, 1.0f), &lampShader, glm::vec3(0.0f, 1.0f, 0.0f));
		//SphericalPointLight sphericalLamp(&ourShader, glm::vec3(-4.0f, 2.0f, 1.0f), &lampShader, glm::vec3(1.0f, 0.0f, 1.0f));
		//CylindricalPointLight cylindricalLamp(&ourShader, glm::vec3(-5.0f, 2.0f, 1.0f), &lampShader, glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
		//cylindricalLamp.scale(glm::vec3(0.0f, 5.0f, 0.0f));

		StreetLamp latarnia(glm::vec3(-2.0f, 0.0f, 3.0f),&ourShader,&lampShader);

		GLfloat rot_angle = 0.75f;
		ourShader.Use();
		

		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		// main event loop
		while (!glfwWindowShouldClose(window))
		{
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			if (deltaTime < 1.0f / MAX_FPS) //limiting rendering to MAX_FPS
				continue;
			lastFrame = currentFrame;

			processInput(window);

			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//rot_angle += 0.01f;
			//if (rot_angle >= 360.0f) rot_angle -= 360.0f;

			ourShader.Use();
			
			ourShader.setVec3("viewPos", camera.Position);

			// light properties
			
			
			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
			ourShader.setMat4("projection", projection);

			// camera/view transformation
			glm::mat4 view = camera.GetViewMatrix();
			ourShader.setMat4("view", view);


			//prostopdaloscian.rotate(glm::vec3(0.0f, rot_angle, 0.0f));
			
			prostopadloscian.draw();
			kostka1.draw();
			kostka2.draw();
			kostka3.draw();
			kostka4.draw();

			cosiek.draw();
			kulka.draw();
			kulka2.draw();
			latarnia.draw();
			tory.draw();

			lampShader.Use();
			lampShader.setMat4("projection", projection);
			lampShader.setMat4("view", view);

			float colorChange = glfwGetTime();

			float colour = (sin(colorChange+5)+1)/2;
			float colour1 = (cos(colorChange+8) + 1) / 2;
			float colour2 = (cos(colorChange+15)*sin(colorChange)*2 + 1) / 2;
			//cubicLamp1.changeColour(glm::vec3(colour, colour1,colour2));;

			//cubicLamp1.move(glm::vec3(0.0f, 0.0f, 0.002f));
			//cubicLamp2.move(glm::vec3(0.0f, 0.0f, 0.004f));
			//cubicLamp3.move(glm::vec3(0.0f, 0.0f, 0.006f));
			//cubicLamp1.draw();
			//cubicLamp2.draw();
			//cubicLamp3.draw();

			//sphericalLamp.draw();
			//cylindricalLamp.draw();
			

			kostka1.rotate(glm::vec3(rot_angle, 0.0f, 0.0f));
			kostka2.rotate(glm::vec3(rot_angle, 0.0f, 0.0f));
			kostka3.rotate(glm::vec3(rot_angle, 0.0f, 0.0f));
			kostka4.rotate(glm::vec3(rot_angle, 0.0f, 0.0f));

			/*kostka1.move(glm::vec3(0.0f, 0.0f, 0.01f));
			kostka2.move(glm::vec3(0.0f, 0.0f, 0.01f));
			kostka3.move(glm::vec3(0.0f, 0.0f, 0.01f));
			kostka4.move(glm::vec3(0.0f, 0.0f, 0.01f));
			prostopadloscian.move(glm::vec3(0.0f, 0.0f, 0.01f));*/

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}
		
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
	glfwTerminate();

	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}