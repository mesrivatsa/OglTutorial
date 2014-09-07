#include <iostream>
#include <string>
#include <vector>

#include "GLShader.h"
#include "GLUtils.h"

GLuint GLShader::LoadShader(const std::string fname, int type)
{
	GLuint vertShader = glCreateShader(type);
	MsgAssert(vertShader != 0, std::string("Error creating shader : ") + fname);

	const std::string shaderCode = LoadFileAsString(fname);
	const GLchar* codeArray[] = { shaderCode.c_str() };
	glShaderSource(vertShader, 1, codeArray, NULL);

	glCompileShader(vertShader);

	GLint result;
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	if (GL_FALSE == result)
	{
		GLint logLen;
		glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);
		if (logLen > 0)
		{
			char * log = new char[logLen];
			GLsizei written;
			glGetShaderInfoLog(vertShader, logLen, &written, log);
			std::cerr << "Shader log:\n" << log;
			delete[] log;
		}
		MsgAssert(false, "Shader compilation failed!");
	}

	return vertShader;
}

GLShader::GLShader(const std::string &fname, int type)
{
	shader_handle = LoadShader(fname, type);
	shader_file = fname;
}

GLuint GLShader::GetHandle() const
{
	return shader_handle;
}

GLProgram::GLProgram(std::vector<GLShader> &shaders)
{
	shader_list = shaders;
	program_handle = Compile(shader_list);
}

GLuint GLProgram::GetHandle() const
{
	return program_handle;
}

GLuint GLProgram::Compile(const std::vector<GLShader> &shaders)
{
	GLuint programHandle = glCreateProgram();
	MsgAssert(programHandle != 0, "Error creating shader program object");

	for (unsigned int cnt = 0; cnt < shaders.size(); cnt++)
	{
		glAttachShader(programHandle, shaders[cnt].GetHandle());
	}

	glLinkProgram(programHandle);

	GLint status;
	glGetProgramiv(programHandle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		GLint logLen;
		glGetProgramiv(programHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if (logLen > 0)
		{
			char * log = (char *)malloc(logLen);
			GLsizei written;
			glGetProgramInfoLog(programHandle, logLen,
				&written, log);
			fprintf(stderr, "Program log: \n%s", log);
			free(log);
		}
		MsgAssert(false, "Failed to link shader program!");
	}
	return programHandle;
}