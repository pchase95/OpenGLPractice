#include <iostream>
#include "Window.h"
#include "Log.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define BUFFER_SIZE 128

Window* Window::instance = nullptr;

Window* Window::Instance()
{
	if (!instance)
	{
		instance = new Window;
	}

	return instance;
}

Window::Window()
	: has_init(false), width(640), height(480), is_open(false)
{
}

void Window::init()
{
	if (!has_init)
	{
		/************** Setup GLFW ****************/
		if (!Log::restart())
		{
			__debugbreak();
		}

		Log::log("Starting GLFW\n%s\n", glfwGetVersionString());

		if (!glfwInit())
		{
			std::cerr << "ERROR: could not create GLFW3 Window" << std::endl;
			exit(EXIT_FAILURE);
		}

		mon = glfwGetPrimaryMonitor();
		const GLFWvidmode* vmode = glfwGetVideoMode(mon);
		win = glfwCreateWindow(width, height, "Memes", 0, 0);
		if (!win)
		{
			Log::logError("GLFW failed to init window\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwSetErrorCallback(glfwErrorCallback);
		glfwSetWindowSizeCallback(win, glfwWindowSizeCallback);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4); // 4x MSAA

		glfwMakeContextCurrent(win);
		/************** Setup GLEW ****************/
		glewExperimental = true;
		if (glewInit() != GLEW_OK)
		{
			Log::logError("GLEW failed to init\n");
			glfwTerminate();
			exit(EXIT_FAILURE);
		}
		/******************************************/

		Log::logGLParams();

		glEnable(GL_DEPTH_TEST); // only draw onto a pixel if it's close to user
		glDepthFunc(GL_LESS); // depth-testing interperts smaller value as "closer"

		const unsigned char* cur_renderer = glGetString(GL_RENDERER);
		const unsigned char* cur_version = glGetString(GL_VERSION);
		Log::log("Renderer: %s\n", cur_renderer);
		Log::log("OpenGL version: %s\n", cur_version);

		is_open = true;
		has_init = true;
	}
}

void Window::updateFPSCounter()
{
	// Update fps counter 4 times per second
	static double previous_seconds = glfwGetTime();
	static int frame_count = 0;
	double current_seconds = glfwGetTime();
	elapsed_seconds = ((float) current_seconds) - ((float)previous_seconds);
	if (elapsed_seconds > 0.25)
	{
		previous_seconds = current_seconds;
		double fps = (double)frame_count / elapsed_seconds;
		char tmp[BUFFER_SIZE];
		sprintf_s(tmp, BUFFER_SIZE, "opengl @ fps: %.2f", fps);
		glfwSetWindowTitle(win, tmp);
		frame_count = 0;
	}
	frame_count++;
}

void Window::poll()
{
	updateFPSCounter();
	glfwSwapBuffers(win);
	glfwPollEvents();
	if (glfwGetKey(win, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(win, 1);
	}

	if (glfwWindowShouldClose(win))
	{
		terminate();
	}
}

void Window::clear()
{
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::terminate()
{
	is_open = false;
	glfwDestroyWindow(win);
	glfwTerminate();
}

void Window::glfwErrorCallback(int error, const char* description)
{
	Log::logError("GLFW Error: code %i msg: %s\n", error, description);
}

void Window::glfwWindowSizeCallback(GLFWwindow* win, int t_width, int t_height)
{
	instance->width = t_width;
	instance->height = t_height;

	/* Update perspective matrices */
}
