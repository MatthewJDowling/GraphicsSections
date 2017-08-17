#include "glinc.h"
#include "../include/graphics/Context.h"
#ifdef _DEBUG
#include <iostream>
void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	std::cerr << message << std::endl;
}
#endif // DEBUG




bool Context::init(size_t w, size_t h, const char *title)
{
	glfwInit();

	handle = glfwCreateWindow(w, h, title, 0, 0);
	glfwMakeContextCurrent(handle);

	glewExperimental = true; 
	glewInit();

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif 

	return true;
}


	


//updating the window
bool Context::step()
{
	glfwPollEvents();
	glfwSwapBuffers(handle);
	return !glfwWindowShouldClose(handle);
}

bool Context::term()
{
	glfwTerminate();
	handle = nullptr;
	return true;
}
bool Context::getKey(int key)
{
	return glfwGetKey(handle, key);
}
double Context::getTime()
{
	return glfwGetTime();
}

void Context::createCustomCursor()
{
	unsigned char pixels[50 * 50 * 4];
	memset(pixels, 0xff, sizeof(pixels));

	for (int i = 0; i < 50*50*4; i+=51*4)
	{
		pixels[i  ] = 255;
		pixels[i+1] = 0;
		pixels[i+2] = 0;
		pixels[i+3] = 255;
	}

	GLFWimage image;
	image.width  = 50;
	image.height = 50;
	image.pixels = pixels;

	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(handle, cursor);
}
