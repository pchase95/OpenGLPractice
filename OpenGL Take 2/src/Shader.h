#pragma once

#include "maths/Maths.h"
#include <unordered_map>

class Shader
{
private:
	std::unordered_map<const char*, int> uniform_locations;
	unsigned int shader_program;
	maths::Vec4 color;

	unsigned int compileShader(const unsigned int& type, const char* source);
	void createShaderProgram(const char* source_file);
	int getUniformLocation(const char* uniform);

	Shader();
public:
	Shader(const char* source_file);
	Shader(const Shader& s);
	Shader(const Shader* s);
	~Shader() {}
	void setUniorm3f(const char* uniform, maths::Vec3 vec);
	void setUniform4f(const char* uniform, maths::Vec4 vec);
	void setUniformMatrix4fv(const char* uniform, const float* mat4);
	void bindAttrib(unsigned int position, const char* name);
	inline unsigned int Get() const { return shader_program; }
	bool isValid() const;
};

