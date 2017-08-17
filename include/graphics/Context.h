#pragma once

//Forward declare GLFW's window
//handling pointer type. 
struct GLFWwindow;

class Context
{
private:
	GLFWwindow *handle;

public:
	bool getKey(int key);
	bool getMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double getTime();
	void createCustomCursor();

	bool init(size_t w = 800, size_t h = 800, 
				const char *title = "Graphics");

	//updating the window
	bool step();

	bool term();
};
