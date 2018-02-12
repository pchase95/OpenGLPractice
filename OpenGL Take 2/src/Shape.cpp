#include "Shape.h"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>
#include <iostream>

Shape::Shape(float* points, size_t points_length, unsigned int method)
	: point_count((int)points_length / 3),
	  vao(0),
	  draw_method(method),
	  attrib_count(0),
	  shader(nullptr)
{
	createVertexObjects(points, points_length);
}

Shape::Shape(float* points, size_t points_length, unsigned int method, Shader t_shader)
	: point_count((int)points_length / 3),
	  vao(0),
	  draw_method(method),
	  attrib_count(0),
	  shader(new Shader(t_shader))
{
	createVertexObjects(points, points_length);
}

Shape::~Shape()
{
	if (shader != nullptr) delete shader;
}

void Shape::draw() const
{
	if (shader != nullptr)
	{
		glUseProgram(shader->Get());
	}
	else
	{
		glUseProgram(0);
	}

	glBindVertexArray(vao);
	glDrawArrays(draw_method, 0, point_count);
}

void Shape::createVertexObjects(float* t_points, size_t t_points_length)
{
	const size_t size = sizeof(float) * t_points_length;
	// Now copy chunk of memory onto Vertex Buffer Object (vbo)
	// var will be a reference to the buffer
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // current buffer is our vbo variable
										// copying chunk of memory stored in points to vbo buffer
	glBufferData(GL_ARRAY_BUFFER, size, t_points, GL_STATIC_DRAW);

	/* Now we set up Vertex Array Object, which memorizes layout of buffer
	Basically, it tells that graphis card that our points array contains positional
	coordinates in groups of 3. */
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// (index of vertex attrib ary to modify, group size, data type, normalize?, gap between points, Where to start)
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
	/* we only have one vertex attrib ary so it's 0
	our ary will contains a position and nothing else */
	glEnableVertexAttribArray(attrib_count++);
}

void Shape::addVBO(float* points, size_t points_length)
{
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, points_length * sizeof(float), points, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(attrib_count++);
}

void Shape::setShader(const Shader& t_shader)
{
	if (shader != nullptr)
	{
		delete shader;
	}

	shader = new Shader(t_shader);
}
