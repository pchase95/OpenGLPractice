#pragma once

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <GL/glew.h>

#define VAR_NAME(var) (#var)

#define GL_LOG_FILE "gl.log"
#define CTIME_DATE_SIZE 26
#define FILE_SIZE 2048
#define NAME_SIZE 64

namespace Log
{
	static bool restart()
	{
		FILE* file;
		fopen_s(&file, GL_LOG_FILE, "w");
		if (!file)
		{
			fprintf(stderr, "Error: could not open GL_LOG_FILE as %s for writing\n", GL_LOG_FILE);
			return false;
		}

		time_t now = time(0);
		char date[CTIME_DATE_SIZE];
		ctime_s(date, CTIME_DATE_SIZE, &now);
		fprintf(file, "GL_LOG_FILE log. local time %s\n", date);
		fclose(file);
		return true;
	}

	static bool log(const char* message, ...)
	{
		va_list argptr;
		FILE* file;
		fopen_s(&file, GL_LOG_FILE, "a");
		if (!file)
		{
			fprintf(stderr, "Error: could not open GL_LOG_FILE as %s for appening\n", GL_LOG_FILE);
			return false;
		}

		va_start(argptr, message);
		vfprintf_s(file, message, argptr);
		va_end(argptr);
		fclose(file);
		return true;
	}

	static bool logError(const char* message, ...)
	{
		va_list argptr;
		FILE* file;
		fopen_s(&file, GL_LOG_FILE, "a");
		if (!file)
		{
			fprintf(stderr, "Error: could not open GL_LOG_FILE as %s for appening\n", GL_LOG_FILE);
			return false;
		}

		va_start(argptr, message);
		vfprintf_s(file, message, argptr);
		va_end(argptr);

		va_start(argptr, message);
		vfprintf_s(stderr, message, argptr);
		va_end(argptr);

		fclose(file);
		return true;
	}

	static void logGLParams()
	{
		unsigned int params[12] {
			GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS,
			GL_MAX_CUBE_MAP_TEXTURE_SIZE,
			GL_MAX_DRAW_BUFFERS,
			GL_MAX_FRAGMENT_UNIFORM_COMPONENTS,
			GL_MAX_TEXTURE_IMAGE_UNITS,
			GL_MAX_TEXTURE_SIZE,
			GL_MAX_VARYING_FLOATS,
			GL_MAX_VERTEX_ATTRIBS,
			GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,
			GL_MAX_VERTEX_UNIFORM_COMPONENTS,
			GL_MAX_VIEWPORT_DIMS,
			GL_STEREO
		};

		const char* names[] {
			"GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS",
			"GL_MAX_CUBE_MAP_TEXTURE_SIZE",
			"GL_MAX_DRAW_BUFFERS",
			"GL_MAX_FRAGMENT_UNIFORM_COMPONENTS",
			"GL_MAX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_TEXTURE_SIZE",
			"GL_MAX_VARYING_FLOATS",
			"GL_MAX_VERTEX_ATTRIBS",
			"GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",
			"GL_MAX_VERTEX_UNIFORM_COMPONENTS",
			"GL_MAX_VIEWPORT_DIMS",
			"GL_STEREO"
		};

		log("GL Context Params:\n");
		for (int i = 0; i < 10; i++)
		{
			int v = 0;
			glGetIntegerv(params[i], &v);
			log("%s %i\n", names[i], params[i]);
		}
		// others
		int v[2] { 0 };
		glGetIntegerv(params[10], v);
		log("%s %i %i\n", names[10], v[0], v[1]);

		unsigned char s = 0;
		glGetBooleanv(params[11], &s);
		log("%s %u\n", names[11], (bool) s);
		log("----------------------------------\n");
	}

	static const char* GLTypeToString(unsigned int type)
	{
		switch (type)
		{
		case GL_BOOL: return "bool";
		case GL_INT: return "int";
		case GL_FLOAT: return "float";
		case GL_FLOAT_VEC2: return "vec2";
		case GL_FLOAT_VEC3: return "vec3";
		case GL_FLOAT_VEC4: return "vec4";
		case GL_FLOAT_MAT2: return "mat2";
		case GL_FLOAT_MAT3: return "mat3";
		case GL_FLOAT_MAT4: return "mat4";
		case GL_SAMPLER_2D: return "sampler2d";
		case GL_SAMPLER_3D: return "sampler3d";
		case GL_SAMPLER_CUBE: return "samplerCube";
		case GL_SAMPLER_2D_SHADOW: return "samplerShader2d";
		default: break;
		}

		return "other";
	}

	static void logShaderInfo(unsigned int shader)
	{
		int length = 0;
		char log[FILE_SIZE];
		glGetShaderInfoLog(shader, FILE_SIZE, &length, log);
		logError("Shader info log for %u:\n%s\n", shader, log);
	}

	static void logShaderProgramInfo(unsigned int shader_program)
	{
		int length = 0;
		char log[FILE_SIZE];
		glGetProgramInfoLog(shader_program, FILE_SIZE, &length, log);
		logError("Info log for shader program %u:\n%s\n", shader_program, log);
	}

	static void logShaderProgramAll(unsigned int shader_program)
	{
		logError("-------------------\nShader Program Info %u Info:\n", shader_program);
		int params = 0;
		glGetProgramiv(shader_program, GL_LINK_STATUS, &params);
		logError("GL_LINK_STATUS = %i\n", params);


		glGetProgramiv(shader_program, GL_ATTACHED_SHADERS, &params);
		logError("GL_ATTACHED_SHADERS = %i\n", params);

		glGetProgramiv(shader_program, GL_ACTIVE_ATTRIBUTES, &params);
		logError("GL_ACTIVE_ATTRIBUTES = %i\n", params);
		for (unsigned int i = 0; i < (unsigned int)params; i++)
		{
			char name[NAME_SIZE];
			int length = 0;
			int size = 0;
			unsigned int type = 0;
			glGetActiveAttrib(shader_program, i, NAME_SIZE, &length, &size, &type, name);

			if (size > 1)
			{
				for (int j = 0; j < size; j++)
				{
					char long_name[NAME_SIZE];
					sprintf_s(long_name, NAME_SIZE, "%s%i", name, j);
					int location = glGetAttribLocation(shader_program, long_name);
					logError("  %i) type: %s, name: %s, location: %i\n",
						i, GLTypeToString(type), name, location);
				}
			}
			else
			{
				int location = glGetAttribLocation(shader_program, name);
				logError("  %i) type: %s, name: %s, location: %i\n",
					i, GLTypeToString(type), name, location);
			}
		}

		glGetProgramiv(shader_program, GL_ACTIVE_UNIFORMS, &params);
		logError("GL_ACTIVE_UNIFORMS = %i\n", params);

		for (unsigned int i = 0; i < (unsigned int)params; i++)
		{
			char name[NAME_SIZE];
			int length = 0;
			int size = 0;
			unsigned int type = 0;
			glGetActiveAttrib(shader_program, i, NAME_SIZE, &length, &size, &type, name);

			if (size > 1)
			{
				for (int j = 0; j < size; j++)
				{
					char long_name[NAME_SIZE];
					sprintf_s(long_name, NAME_SIZE, "%s%i", name, j);
					int location = glGetUniformLocation(shader_program, long_name);
					logError("  %i) type: %s, name: %s, location: %i\n",
						i, GLTypeToString(type), name, location);

				}
			}
			else
			{
				int location = glGetUniformLocation(shader_program, name);
				logError("  %i) type: %s, name: %s, location: %i\n",
					i, GLTypeToString(type), name, location);
			}
		}
	}
}
