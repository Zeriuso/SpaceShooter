#pragma once
#include "../Renderer/ShaderProgram.h"
#include <map>
#include <string>
#include <memory>

class ResourceManager {
public:
	ResourceManager() = delete;
	~ResourceManager() = delete;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;
	ResourceManager(ResourceManager&&) = delete;

	static std::shared_ptr<ShaderProgram> LoadShader(const std::string& vShaderFile, const std::string& fShaderFile, std::string name);
	
	static std::shared_ptr<ShaderProgram> GetShaderProgram(const std::string name);

	static void Clear();

private:
	static std::string FileToString(const std::string& shaderFile);

	static std::map<std::string, std::shared_ptr<ShaderProgram>> m_ShaderPrograms;
};