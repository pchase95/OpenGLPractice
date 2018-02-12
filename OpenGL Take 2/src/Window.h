#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class Window
{
private:
	static Window* instance;

	bool has_init;
	bool is_open;
	GLFWwindow* win;
	GLFWmonitor* mon;

	int width;
	int height;

	Window();
	Window(const Window& w) = delete;
	Window& operator=(const Window& w) = delete;
	~Window() {}

	void updateFPSCounter();

	static void glfwErrorCallback(int error, const char* description);
	static void glfwWindowSizeCallback(GLFWwindow* win, int width, int height);
public:
	static Window* Instance();

	void init();
	void terminate();
	void poll();
	inline GLFWwindow* Get() const { return win; }
	inline int Width() { return width; }
	inline int Height() { return height; }
	inline bool IsOpen() { return is_open; }
};
