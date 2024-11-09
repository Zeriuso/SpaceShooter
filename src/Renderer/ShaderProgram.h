#pragma once

#include <string>
#include <glad/glad.h>

class ShaderProgram {
public:
	ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgram() = default;
	~ShaderProgram();
	ShaderProgram(const ShaderProgram&) = delete;
	ShaderProgram& operator=(const ShaderProgram&) = delete;
	ShaderProgram& operator=(ShaderProgram&& shaderProgram) = delete;
	ShaderProgram(ShaderProgram&& shaderProgram) = delete;

	void Use() const;

private:
	bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
	bool CheckCompileErrors(GLuint shader, GLenum shaderType);
	void CheckLinkErrors(GLuint shaderID);

	GLuint m_ID = 0;
};