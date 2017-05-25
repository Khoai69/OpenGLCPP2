#include <stdio.h>
#include <stdlib.h>
#include "Utils\ogles_sys.h"
#include <string>
#include "ShaderProgram.h"



ShaderProgram::ShaderProgram()
{
}

ShaderProgram::~ShaderProgram()
{
}

ShaderProgram::ShaderProgram(const char* vs, const char * fs, const char* program_name)
{
	m_programName = program_name;
	Create(vs, fs);
}
ShaderProgram::ShaderProgram(const char* vs, const char * fs)
{
	Create(vs, fs);
}
GLuint ShaderProgram::Create(const char* vs, const char * fs)
{
	GLuint vertex = LoadShader(GL_VERTEX_SHADER, vs);
	GLuint fragment = LoadShader(GL_FRAGMENT_SHADER, fs);
	return LoadProgram(vertex, fragment);
}

GLuint  ShaderProgram::LoadShader(GLenum type, const char * filename)
{
	GLuint shader;
	GLint compiled;

	// Create the shader object
	shader = glCreateShader(type);

	if (shader == 0)
		return 0;

	// Load the shader source
	FILE * pf;
	if (fopen_s(&pf, filename, "rb") != 0)
		return NULL;
	fseek(pf, 0, SEEK_END);
	long size = ftell(pf);
	fseek(pf, 0, SEEK_SET);

	char * shaderSrc = new char[size + 1];
	fread(shaderSrc, sizeof(char), size, pf);
	shaderSrc[size] = 0;
	fclose(pf);

	glShaderSource(shader, 1, (const char **)&shaderSrc, NULL);
	delete[] shaderSrc;

	// Compile the shader
	glCompileShader(shader);

	// Check the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLint infoLen = 0;

		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[infoLen];


			glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
			LOG("\nError compiling shader <%s> :\n%s\n", filename,infoLog);

			delete[] infoLog;
		}

		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

GLuint  ShaderProgram::LoadProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint programObject;
	GLint linked;

	// Create the program object
	programObject = glCreateProgram();

	if (programObject == 0)
	{
		LOG("\nFailed to create program");
		return 0;
	}
		

	glAttachShader(programObject, vertexShader);
	glAttachShader(programObject, fragmentShader);

	// Link the program
	glLinkProgram(programObject);

	// Check the link status
	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);

	if (!linked)
	{
		GLint infoLen = 0;

		glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

		if (infoLen > 1)
		{
			char* infoLog = new char[sizeof(char) * infoLen];


			glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
			LOG("\nError linking program <%s>:\n%s\n", m_programName.c_str(), infoLog);

			delete infoLog;
		}
		LOG("\nFailed to create program");
		glDeleteProgram(programObject);
		return 0;
	}
	LOG("\nCreate program <%s> success ID = %d", m_programName.c_str(), programObject);
	m_programid = programObject;
	return programObject;
}