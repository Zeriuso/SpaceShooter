#include "ShaderProgram.h"

#include <iostream>
#include <unordered_map>

ShaderProgram::ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource)
{
	GLuint vertexShader;
	if (!CreateShader(vertexSource, GL_VERTEX_SHADER, vertexShader))
	{
		std::cerr << "VERTEX SHADER creation error" << std::endl;
		return;
	}

	GLuint fragmentShader;
	if (!CreateShader(fragmentSource, GL_FRAGMENT_SHADER, fragmentShader))
	{
		std::cerr << "FRAGMENT SHADER creation error" << std::endl;
		glDeleteShader(vertexShader);
		return;
	}

	m_ID = glCreateProgram();
	glAttachShader(m_ID, vertexShader);
	glAttachShader(m_ID, fragmentShader);
	glLinkProgram(m_ID);
	CheckLinkErrors(m_ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

bool ShaderProgram::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shader)
{
	shader = glCreateShader(shaderType);
	const char* code = source.c_str();
	glShaderSource(shader, 1, &code, nullptr);
	glCompileShader(shader);
	if (!CheckCompileErrors(shader, shaderType))
	{
		return false;
	}
	return true;
}

bool ShaderProgram::CheckCompileErrors(GLuint shader, GLenum shaderType)
{
	std::unordered_map<GLenum, std::string> typeMap = {
			{GL_VERTEX_SHADER, "GL_VERTEX_SHADER"},
			{GL_FRAGMENT_SHADER, "GL_FRAGMENT_SHADER"}
	};

	std::string type = typeMap[shaderType];

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetProgramInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::SHADER: Compile-time error: Type: "
			<< type << "/n" << infoLog << std::endl;
		return false;
	}
	return true;
}

void ShaderProgram::CheckLinkErrors(GLuint shaderID)
{
	GLint success;
	glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetProgramInfoLog(shaderID, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_ID);
}

void ShaderProgram::Use() const
{
	glUseProgram(m_ID);
}