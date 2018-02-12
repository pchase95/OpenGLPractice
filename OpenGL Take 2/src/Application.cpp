#include "Shape.h"
#include "Window.h"
#include "Shader.h"
#include "Maths.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main()
{
	Window::Instance()->init();
	Shader rainbow("res/rainbow.shader");

	float points[9] {
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5,  -0.5,  0.0f
	};

	float colors[9] {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	Shape tri(points, 9, GL_TRIANGLES, rainbow);
	tri.addVBO(colors, 9);

	while (Window::Instance()->IsOpen())
	{
		glViewport(0, 0, Window::Instance()->Width(), Window::Instance()->Height());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Draw stuff here */
		tri.draw();
		/* *************** */

		Window::Instance()->poll();
	}
}
