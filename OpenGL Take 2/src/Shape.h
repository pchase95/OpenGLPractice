#pragma once

#include "Shader.h"
#include <GL/glew.h>
#include <array>

class Shape
{
private:
	int point_count;
	unsigned int vao;
	unsigned int draw_method;
	unsigned int attrib_count;
	Shader* shader;

	Shape(const Shape& s) = delete;
	Shape() = delete;
	void createVertexObjects(std::array<float, 9> points);
public:
	Shape(std::array<float, 9> points, unsigned int method);
	Shape(std::array<float, 9> points, unsigned int method, Shader t_shader);
	~Shape();

	void draw() const;
	void setShader(const Shader& t_shader);
	void addVBO(std::array<float, 9> points);

	inline Shader* getShader() const { return shader; }
	inline unsigned int DrawMethod() const { return draw_method; }
	inline void setDrawMethod(unsigned int method) { draw_method = method; }
};
