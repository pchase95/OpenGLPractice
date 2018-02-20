#include "Shape.h"
#include "Window.h"
#include "Shader.h"
#include "maths/Maths.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <array>

int main()
{
	Window::Instance()->init();
	Shader rainbow("res/rainbow.shader");

	std::array<float, 9> points {
		-0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f
	};

	std::array<float, 9> colors {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	Shape tri(points, GL_TRIANGLES, rainbow);
	tri.addVBO(colors);

	maths::Mat4 scale = maths::Mat4::Scale(maths::Vec3(1.5f, 1.5, 1.0));

	maths::Mat4 rot = maths::Mat4::Rotate(90.0f, maths::Vec3(0.5f, 0.0f, 1.0));

	maths::Mat4 out = maths::Mat4::Identity() * scale * rot;

	rainbow.setUniformMatrix4fv("u_matrix", out);

	while (Window::Instance()->IsOpen())
	{
		Window::Instance()->clear();

		tri.draw();

		Window::Instance()->poll();
	}
}
