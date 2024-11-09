#include "ResourceManager.h"
#include <iostream>
#include <sstream>
#include <fstream>

std::map<std::string, std::shared_ptr<ShaderProgram>> ResourceManager::m_ShaderPrograms;

std::string ResourceManager::FileToString(const std::string& shaderFile)
{
	std::stringstream shaderStream;
	try
	{
		std::ifstream shaderFile(shaderFile);

		shaderStream << shaderFile.rdbuf();

		shaderFile.close();
	}
	catch (const std::exception&)
	{
		std::cerr << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	return shaderStream.str();;
}

std::shared_ptr<ShaderProgram> ResourceManager::LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, const std::string name)
{
	std::string vShaderCode = FileToString(vShaderFile);
	std::string fShaderCode = FileToString(fShaderFile);

	std::shared_ptr<ShaderProgram> newShader = std::make_shared<ShaderProgram>(vShaderCode, fShaderCode);
	
	m_ShaderPrograms.emplace(name, newShader);

	return m_ShaderPrograms[name];
}

std::shared_ptr<ShaderProgram> ResourceManager::GetShaderProgram(const std::string name)
{
	auto it = m_ShaderPrograms.find(name);
	if (it != m_ShaderPrograms.end())
	{
		return it->second;
	}
	std::cerr << "Can't find the shader program: " << name << std::endl;
	return nullptr;
}

void ResourceManager::Clear()
{
	m_ShaderPrograms.clear();
}