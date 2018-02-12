#pragma once

#include "Shader.h"
#include <GL/glew.h>

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
	void createVertexObjects(float* points, size_t points_length);
public:
	Shape(float* t_points, size_t t_point_count, unsigned int method);
	Shape(float* t_points, size_t t_point_count, unsigned int method, Shader t_shader);
	~Shape();

	void draw() const;
	void setShader(const Shader& t_shader);
	void addVBO(float* points, size_t points_length);

	inline Shader* getShader() const { return shader; }
	inline unsigned int DrawMethod() const { return draw_method; }
	inline void setDrawMethod(unsigned int method) { draw_method = method; }
};
