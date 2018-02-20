#include "Shader.h"
#include "maths/Maths.h"
#include "Log.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <GL/glew.h>

#define LINE_SIZE 256
#define FILE_SIZE 2048

Shader::Shader()
	: shader_program(0)
{
}

Shader::Shader(const char* source_file)
	: shader_program(0)
{
	createShaderProgram(source_file);
}

Shader::Shader(const Shader& s)
	: shader_program(s.shader_program)
{
}

Shader::Shader(const Shader* s)
	: Shader(*s)
{
}

unsigned int Shader::compileShader(const unsigned int& type, const char* source)
{
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);
	
	int params = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &params);
	if (!params)
	{
		Log::logError("ERROR: GL shader index %u did not compile\n", shader);
		Log::logShaderInfo(shader);
		__debugbreak();
	}

	return shader;
}

void Shader::createShaderProgram(const char* source_file)
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	FILE* file;
	fopen_s(&file, source_file, "r");
	if (!file)
	{
		Log::logError("Could not open shader source: %s\n", source_file);
		__debugbreak();
		exit(EXIT_FAILURE);
	}
	char line[LINE_SIZE];
	char* vertex_source = (char*)alloca(FILE_SIZE);
	memset(vertex_source, 0, FILE_SIZE);
	char* fragment_source = (char*)alloca(FILE_SIZE);
	memset(fragment_source, 0, FILE_SIZE);

	ShaderType type = ShaderType::NONE;
	while (fgets(line, LINE_SIZE, file))
	{
		if (strstr(line, "#shader"))
		{
			if (strstr(line, "vertex"))
			{
				type = ShaderType::VERTEX;
			}
			else if (strstr(line, "fragment"))
			{
				type = ShaderType::FRAGMENT;
			}
			continue;
		}

		if (type == ShaderType::VERTEX)
		{
			strcat_s(vertex_source, FILE_SIZE, line);
		}
		else if (type == ShaderType::FRAGMENT)
		{
			strcat_s(fragment_source, FILE_SIZE, line);
		}
	}
	fclose(file);

	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertex_source);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragment_source);

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vs);
	glAttachShader(shader_program, fs);
	
	glLinkProgram(shader_program);

	int params = 0;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &params);
	if (!params)
	{
		Log::logError("ERROR: Could not link shader program %u\n", shader_program);
		Log::logShaderProgramInfo(shader_program);
		__debugbreak();
	}
}

void Shader::bindAttrib(unsigned int position, const char* name)
{
	glBindAttribLocation(shader_program, position, name);
}

int Shader::getUniformLocation(const char* uniform)
{
	if (uniform_locations.count(uniform) > 0)
	{
		return uniform_locations[uniform];
	}

	int location = glGetUniformLocation(shader_program, uniform);
	if (location == -1)
	{
		Log::logError("ERROR: Could not find shader uniform");
		__debugbreak();
	}
	uniform_locations[uniform] = location;
	return location;
}

void Shader::setUniorm3f(const char* uniform, maths::Vec3 vec)
{
	int location = getUniformLocation(uniform);
	glUseProgram(shader_program);
	glUniform3f(location, vec.x, vec.y, vec.z);
}

void Shader::setUniform4f(const char* uniform, maths::Vec4 vec)
{
	int location = getUniformLocation(uniform);
	glUseProgram(shader_program);
	glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void Shader::setUniformMatrix4fv(const char* uniform, const maths::Mat4& mat4)
{
	int location = getUniformLocation(uniform);
	glUseProgram(shader_program);
	glUniformMatrix4fv(location, 1, false, mat4.Get());
}

bool Shader::isValid() const
{
	glValidateProgram(shader_program);
	int params = 0;
	glGetProgramiv(shader_program, GL_VALIDATE_STATUS, &params);
	Log::logError("program %u GL_VALIDATE_STATUS = %i\n", shader_program, params);
	if (!params)
	{
		Log::logShaderProgramInfo(shader_program);
		return false;
	}

	return true;
}
