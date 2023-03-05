#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

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

	std::shared_ptr<Renderer::ShaderProgram>& newShader =
		m_sharedPrograms.emplace(shaderName, std::make_shared<Renderer::ShaderProgram>(vertexString, fragmentString)).first->second;

	if (!(newShader->isCompiled()))
	{
		std::cerr << shaderName << " not loaded!" << std::endl;
		return nullptr;
	}

	return newShader;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	if (!(m_sharedPrograms.count(shaderName)))
	{
		std::cerr << "Can't find the shader program: " << shaderName << '!' << std::endl;
		return nullptr;
	}

	return m_sharedPrograms[shaderName];
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

std::shared_ptr<Renderer::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	// we need to use this function because by default "stbi" starts reading the file from the upper left corner,
	// OpenGL does it from lower left corner, this function changes the default stbi settings
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixeles = stbi_load(std::string(m_Path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixeles)
	{
		std::cerr << "Can't load Image: " << texturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::Texture2D> newTexture = m_textures.emplace(textureName,
			std::make_shared<Renderer::Texture2D>(width, height, pixeles, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixeles);

	if (!newTexture)
	{
		std::cerr << "Can't load Texture: " << textureName << std::endl;
	}

	return newTexture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	if (!(m_textures.count(textureName)))
	{
		std::cerr << "Can't find the shader program: " << textureName << '!' << std::endl;
		return nullptr;
	}

	return m_textures[textureName];
}