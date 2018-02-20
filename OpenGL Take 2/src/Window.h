#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

	float elapsed_seconds;

	Window();
	Window(const Window& w) = delete;
	Window& operator=(const Window& w) = delete;
	~Window() {}

	void updateFPSCounter();
	void terminate();

	static void glfwErrorCallback(int error, const char* description);
	static void glfwWindowSizeCallback(GLFWwindow* win, int width, int height);
public:
	static Window* Instance();

	void init();
	void poll();
	void clear();
	inline GLFWwindow* Get() const { return win; }
	inline int Width() { return width; }
	inline int Height() { return height; }
	inline bool IsOpen() { return is_open; }
	inline float ElapsedSeconds() { return elapsed_seconds; }
};
