#include "Shape.h"
#include <GL/glew.h>
#include <cstdio>
#include <cstring>
#include <iostream>

Shape::Shape(std::array<float, 9> points, unsigned int method)
	: point_count(3),
	  vao(0),
	  draw_method(method),
	  attrib_count(0),
	  shader(nullptr)
{
	createVertexObjects(points);
}

Shape::Shape(std::array<float, 9> points, unsigned int method, Shader t_shader)
	: point_count(3),
	  vao(0),
	  draw_method(method),
	  attrib_count(0),
	  shader(new Shader(t_shader))
{
	createVertexObjects(points);
}

Shape::~Shape()
{
	if (shader != nullptr) delete shader;
}

void Shape::draw() const
{
	glUseProgram(shader->Get());
	glBindVertexArray(vao);
	glDrawArrays(draw_method, 0, point_count);
}

void Shape::createVertexObjects(std::array<float, 9> points)
{
	const size_t size = sizeof(float) * 9;
	// Now copy chunk of memory onto Vertex Buffer Object (vbo)
	// var will be a reference to the buffer
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // current buffer is our vbo variable
										// copying chunk of memory stored in points to vbo buffer
	glBufferData(GL_ARRAY_BUFFER, size, points.data(), GL_STATIC_DRAW);

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

void Shape::addVBO(std::array<float, 9> points)
{
	unsigned int vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points.data(), GL_STATIC_DRAW);
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
