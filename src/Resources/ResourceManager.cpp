#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_Path = executablePath.substr(0, found);
}

std::shared_ptr<Renderer::ShaderProgram>
ResourceManager::loadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexString = getFileString(vertexPath);
	if (vertexString.empty())
	{
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr; 
	}

	std::string fragmentString = getFileString(fragmentPath);
	if (fragmentString.empty())
	{
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}

	m_SharedPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString));
	std::shared_ptr<Renderer::ShaderProgram>& newShader = m_SharedPrograms[shaderName];

	if (!(newShader->isCompiled()))
	{
		std::cerr << shaderName << "not loaded!" << std::endl;
		return nullptr;
	}

	return newShader;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	if (!(m_SharedPrograms.count(shaderName)))
	{
		std::cerr << "Can't find the shader program: " << shaderName << '!' << std::endl;
		return nullptr;
	}

	return m_SharedPrograms[shaderName];
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath) const
{
	std::ifstream f;
	f.open(m_Path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed to open " << relativeFilePath << " file!" << std::endl;
		return std::string();
	}

	std::stringstream buff;
	buff << f.rdbuf();

	return buff.str();
}