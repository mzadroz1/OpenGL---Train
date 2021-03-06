#define GLEW_STATIC
#include <GL/glew.h>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <math.h>
#include "StreetLamp.h"

#include "Train.h"
#include "TrainChassis.h"
#include "TrainBody.h"
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
#include "Skybox.h"
#include "Floor.h"
#include "Car.h"
#include "Road.h"
#include "Barrier.h"
#include "Semaphore.h"
#include "Cargo.h"

const float MAX_FPS = 60.0f;
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
int PointLight::pointLightsQuantity = 0; //init static variable of PointLight

typedef struct {
	double r;       // a fraction between 0 and 1
	double g;       // a fraction between 0 and 1
	double b;       // a fraction between 0 and 1
} rgb;

typedef struct {
	double h;       // angle in degrees
	double s;       // a fraction between 0 and 1
	double v;       // a fraction between 0 and 1
} hsv;

static hsv   rgb2hsv(rgb in);
static rgb   hsv2rgb(hsv in);

hsv rgb2hsv(rgb in)
{
	hsv         out;
	double      min, max, delta;

	min = in.r < in.g ? in.r : in.g;
	min = min < in.b ? min : in.b;

	max = in.r > in.g ? in.r : in.g;
	max = max > in.b ? max : in.b;

	out.v = max;                                // v
	delta = max - min;
	if (delta < 0.00001)
	{
		out.s = 0;
		out.h = 0; // undefined, maybe nan?
		return out;
	}
	if (max > 0.0) { // NOTE: if Max is == 0, this divide would cause a crash
		out.s = (delta / max);                  // s
	}
	else {
		// if max is 0, then r = g = b = 0              
		// s = 0, h is undefined
		out.s = 0.0;
		out.h = NAN;                            // its now undefined
		return out;
	}
	if (in.r >= max)                           // > is bogus, just keeps compilor happy
		out.h = (in.g - in.b) / delta;        // between yellow & magenta
	else
		if (in.g >= max)
			out.h = 2.0 + (in.b - in.r) / delta;  // between cyan & yellow
		else
			out.h = 4.0 + (in.r - in.g) / delta;  // between magenta & cyan

	out.h *= 60.0;                              // degrees

	if (out.h < 0.0)
		out.h += 360.0;

	return out;
}


rgb hsv2rgb(hsv in)
{
	double      hh, p, q, t, ff;
	long        i;
	rgb         out;

	if (in.s <= 0.0) {       // < is bogus, just shuts up warnings
		out.r = in.v;
		out.g = in.v;
		out.b = in.v;
		return out;
	}
	hh = in.h;
	if (hh >= 360.0) hh = 0.0;
	hh /= 60.0;
	i = (long)hh;
	ff = hh - i;
	p = in.v * (1.0 - in.s);
	q = in.v * (1.0 - (in.s * ff));
	t = in.v * (1.0 - (in.s * (1.0 - ff)));

	switch (i) {
	case 0:
		out.r = in.v;
		out.g = t;
		out.b = p;
		break;
	case 1:
		out.r = q;
		out.g = in.v;
		out.b = p;
		break;
	case 2:
		out.r = p;
		out.g = in.v;
		out.b = t;
		break;

	case 3:
		out.r = p;
		out.g = q;
		out.b = in.v;
		break;
	case 4:
		out.r = t;
		out.g = p;
		out.b = in.v;
		break;
	case 5:
	default:
		out.r = in.v;
		out.g = p;
		out.b = q;
		break;
	}
	return out;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	cout << key << endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void setUpShaders(ShaderProgram* shader, ShaderProgram* lampShader, ShaderProgram* skyboxShader);
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
Camera camera(glm::vec3(-1.0f, 2.0f, 10.0f));
float lastX = 800 / 2.0f;
float lastY = 600 / 2.0f;
bool firstMouse = true;
// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
GLuint WIDTH;
GLuint HEIGHT;
long frameCounter = 0;

glm::vec3 train_speed = { 0.0f,0.0f,0.0f };
float lightBrightness = 0.0;

int main() {
	if (glfwInit() != GL_TRUE) {
		cout << "GLFW initialization failed" << endl;
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	try {
		WIDTH = glfwGetVideoMode(glfwGetPrimaryMonitor())->width;
		HEIGHT = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;
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
		ShaderProgram skyboxShader("SkyboxShader.vert", "SkyboxShader.frag");

		Tracks tory(glm::vec3(0.0f, 0.0f, -50.0f), 100, &ourShader);
		Semaphore semafor(glm::vec3(-3.f, 0.f, 18.f), &ourShader, &lampShader);
		
		//cylindricalLamp.scale(glm::vec3(0.0f, 5.0f, 0.0f));
		Skybox skybox = Skybox(skyboxShader);
		Floor floor = Floor(glm::vec3(0, -0.1, 0), &ourShader);
		Road road = Road(glm::vec3(-200.0, -0.05, 15.0), 20, &ourShader);
		Barrier barrier = Barrier({-2, 0.3, 18}, &ourShader);

		SphericalPointLight rainbow = SphericalPointLight(&ourShader, glm::vec3(0.0f, 4.0f, 5.0f), &lampShader, { 0.5,0.5,0.5 }, { 0.25,0.25,0.25 });
	

		StreetLamp* latarnie[10];
		for (int i = 0; i < 10; i++) {
			latarnie[i] = new StreetLamp(glm::vec3(5.0f, 0.0f, 10.0f * i), &ourShader, &lampShader);
		}
		Cargo cargo(glm::vec3(0.f, 0.f, -8.f), 2, &ourShader);
		Train ciopong({ 0,0,1 }, &ourShader, &lampShader);
		Car* cars[4];
		const char*  bodyTextures[] = { "textures/red_metal.png", "textures/yellow_metal.png", "textures/blue_metal.png", "textures/green_metal.png" };
		for (int i = 0; i < 4; i++) {
			cars[i] = new Car({ -6 - 6*i, 0.6, 16.25 }, &ourShader, &lampShader, bodyTextures[i]);
		}
		hsv color;
		color.h = 0.0f; color.v = 1.0; color.s = 0.9;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// main event loop
		while (!glfwWindowShouldClose(window)) {
			// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
			glfwPollEvents();
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			if (deltaTime < 1.0f / MAX_FPS) //limiting rendering to MAX_FPS
				continue;
			lastFrame = currentFrame;
			processInput(window);

			if (frameCounter > MAX_FPS * 17) frameCounter = 0;
			if (frameCounter == 0) semafor.changeToGreen();
			else if (frameCounter == MAX_FPS * 5) semafor.changeToYellow();
			else if (frameCounter == MAX_FPS * 7) semafor.changeToRed();
			else if (frameCounter == MAX_FPS * 15) semafor.changeToYellowRed();
			frameCounter++;
			
			// Clear the colorbuffer
			glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			setUpShaders(&ourShader, &lampShader, &skyboxShader);
			
			skybox.draw();
			floor.draw();
			tory.draw();
			semafor.draw();
			
			for (int i = 0; i < 10; i++) {
				latarnie[i]->draw();
			}

			
			for (int i = 0; i < 4; i++) {
				cars[i]->draw();
			}
			barrier.draw();
			road.draw();
			rainbow.draw();
			cargo.draw();
			ciopong.draw();
			cargo.move(train_speed);
			ciopong.move(train_speed);
			rainbow.move(train_speed);

			if (color.h == 360.0f)
				color.h = 0.0f;
			color.h +=1.0f;
			rgb c = hsv2rgb(color);
			rainbow.changeColour({ c.r,c.g,c.b });
			ciopong.setLightsBrightness(lightBrightness);

			// Swap the screen buffers
			glfwSwapBuffers(window);
		}

	} catch (exception ex) {
		cout << ex.what() << endl;
	}
	glfwTerminate();
	return 0;
}

void setUpShaders(ShaderProgram* shader, ShaderProgram* lampShader, ShaderProgram* skyboxShader)
{
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera.GetViewMatrix();
	
	shader->Use();
	shader->setVec3("viewPos", camera.Position);
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);

	lampShader->Use();
	lampShader->setMat4("projection", projection);
	lampShader->setMat4("view", view);

	skyboxShader->Use();
	view = glm::mat4(glm::mat3(view));
	skyboxShader->setMat4("view", view);
	skyboxShader->setMat4("projection", projection);
}

void processInput(GLFWwindow* window) {
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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		train_speed.z += 0.0005f;
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		train_speed.z -= 0.0005f;


	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) //increase brightness 
		lightBrightness = 0.01;
	else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) //decrease brightness
		lightBrightness = -0.01;
	else
		lightBrightness = 0.0;
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
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
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}