#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ShaderProgramsMap ResourceManager::m_shaderPrograms;
ResourceManager::TexturesMap ResourceManager::m_textures;
ResourceManager::SpritesMap ResourceManager::m_sprites;
std::vector<std::vector<std::string>> ResourceManager::m_levels;
std::string ResourceManager::m_Path;

void ResourceManager::setExecutablePath(const std::string& executablePath)
{
	size_t found = executablePath.find_last_of("/\\");
	m_Path = executablePath.substr(0, found);
}

void ResourceManager::unloadAllResources()
{
	m_shaderPrograms.clear();
	m_textures.clear();
	m_sprites.clear();
	m_Path.clear();
}

std::shared_ptr<RenderEngine::ShaderProgram>
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

	std::shared_ptr<RenderEngine::ShaderProgram>& newShader = m_shaderPrograms.emplace(shaderName,
		std::make_shared<RenderEngine::ShaderProgram>(vertexString, fragmentString)).first->second;

	if (!(newShader->isCompiled()))
	{
		std::cerr << shaderName << " not loaded!" << std::endl;
		return nullptr;
	}

	return newShader;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::getShaderProgram(const std::string& shaderName)
{
	if (!(m_shaderPrograms.count(shaderName)))
	{
		std::cerr << "Can't find the shader program: " << shaderName << '!' << std::endl;
		return nullptr;
	}

	return m_shaderPrograms[shaderName];
}

std::string ResourceManager::getFileString(const std::string& relativeFilePath)
{
	std::ifstream f;
	f.open(m_Path + "/" + relativeFilePath, std::ios::in | std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Failed to open " << relativeFilePath << " file!" << std::endl;
		return std::string{};
	}

	std::stringstream buff;
	buff << f.rdbuf();

	return buff.str();
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTexture(const std::string& textureName, const std::string& texturePath)
{
	int channels = 0;
	int width = 0;
	int height = 0;

	// we need to use this function because by default "stbi" starts reading the file from the upper left corner,
	// OpenGL does it from lower left corner, this function changes the default stbi settings
	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(m_Path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

	if (!pixels)
	{
		std::cerr << "Can't load Image: " << texturePath << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Texture2D> newTexture = m_textures.emplace(textureName,
		std::make_shared<RenderEngine::Texture2D>(width, height, pixels, channels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);

	if (!newTexture)
	{
		std::cerr << "Can't load texture: " << textureName << std::endl;
	}

	return newTexture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::getTexture(const std::string& textureName)
{
	if (!(m_textures.count(textureName)))
	{
		std::cerr << "Can't find the texture: " << textureName << '!' << std::endl;
		return nullptr;
	}

	return m_textures[textureName];
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::loadSprite
(	const std::string& spriteName,
	const std::string& textureName,
	const std::string& shaderName,
	const std::string& subTextureName)
{
	auto pTexture = getTexture(textureName);
	if (!pTexture)
	{
		std::cerr << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << std::endl;
		return nullptr;
	}

	auto pShaderProgram = getShaderProgram(shaderName);
	if (!pShaderProgram)
	{
		std::cerr << "Can't find the shader program: " << shaderName << " for the sprite: " << spriteName << std::endl;
		return nullptr;
	}

	std::shared_ptr<RenderEngine::Sprite>& newSprite = m_sprites.emplace(spriteName, std::make_shared<RenderEngine::Sprite>(pTexture, subTextureName, pShaderProgram)).first->second;

	return newSprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::getSprite(const std::string& spriteName)
{
	if (!(m_sprites.count(spriteName)))
	{
		std::cerr << "Can't find the sprite: " << spriteName << '!' << std::endl;
		return nullptr;
	}

	return m_sprites[spriteName];
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::loadTextureAtlas(std::string textureName, std::string texturePath,
	std::vector<std::string> subTextures, const unsigned subTextureWidth, const unsigned subTextureHeight)
{
	auto pTexture = loadTexture(std::move(textureName), std::move(texturePath));

	if (pTexture)
	{
		const unsigned textureWidth = pTexture->width();
		const unsigned textureHeight = pTexture->height();
		unsigned currentTextureOffsetX = 0;
		unsigned currentTextureOffsetY = textureHeight;

		for (auto& currentSubTextureName : subTextures)
		{
			glm::vec2 leftBottomUV(static_cast<float>(currentTextureOffsetX + 0.2f) / textureWidth,
				static_cast<float>(currentTextureOffsetY + 0.2f - subTextureHeight) / textureHeight);
			glm::vec2 rightTopUV(static_cast<float>(currentTextureOffsetX - 0.2f + subTextureWidth) / textureWidth,
				static_cast<float>(currentTextureOffsetY - 0.2f) / textureHeight);
			pTexture->addSubTexture(std::move(currentSubTextureName), leftBottomUV, rightTopUV);

			currentTextureOffsetX += subTextureWidth;
			if (currentTextureOffsetX >= textureWidth)
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHeight;
			}
		}
	}

	return pTexture;
}

bool ResourceManager::loadJSONResources(const std::string& JSONPath)
{
	const std::string JSONString = getFileString(JSONPath);

	if (JSONString.empty())
	{
		std::cerr << "No JSON resources file!" << std::endl;
		return false;
	}

	rapidjson::Document document;
	rapidjson::ParseResult parseResult = document.Parse(JSONString.c_str());
	if (!parseResult)
	{
		std::cerr << "JSON parse error: " << rapidjson::GetParseError_En(parseResult.Code()) << "(" << parseResult.Offset() << ")" << std::endl
			<< "In JSON file" << JSONPath << std::endl;
		return false;
	}
	
	auto shadersIt = document.FindMember("shaders");
	if (shadersIt != document.MemberEnd())
	{
		for (const auto& currentShader : shadersIt->value.GetArray())
		{
			const std::string name = currentShader["name"].GetString();
			const std::string filePath_v = currentShader["filePath_v"].GetString();
			const std::string filePath_f = currentShader["filePath_f"].GetString();

			loadShaders(name, filePath_v, filePath_f);
		}
	}

	auto texturesAtlasesIt = document.FindMember("textureAtlases");
	if (texturesAtlasesIt != document.MemberEnd())
	{
		for (const auto& currentTextureAtlas : texturesAtlasesIt->value.GetArray())
		{
			const std::string name = currentTextureAtlas["name"].GetString();
			const std::string filePath = currentTextureAtlas["filePath"].GetString();
			const unsigned subTextureWidth = currentTextureAtlas["subTextureWidth"].GetInt();
			const unsigned subTextureHeight = currentTextureAtlas["subTextureHeight"].GetInt();
			const auto subTexturesArray = currentTextureAtlas["subTextures"].GetArray();

			std::vector<std::string> subTextures;
			subTextures.reserve(subTexturesArray.Size());

			for (const auto& currentSubTexture : subTexturesArray)
			{
				subTextures.emplace_back(currentSubTexture.GetString());
			}

			loadTextureAtlas(name, filePath, std::move(subTextures), subTextureWidth, subTextureHeight);
		}
	}

	auto spritesIt = document.FindMember("sprites");
	if (spritesIt != document.MemberEnd())
	{
		for (const auto& currentSprite : spritesIt->value.GetArray())
		{
			const std::string name = currentSprite["name"].GetString();
			const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
			const std::string shaderName = currentSprite["shader"].GetString();
			const std::string subTextureName = currentSprite["initialSubTexture"].GetString();

			auto pSprite = loadSprite(name, textureAtlas, shaderName, subTextureName);

			auto frameIt = currentSprite.FindMember("frames");
			if (frameIt != currentSprite.MemberEnd())
			{
				const auto framesArray = frameIt->value.GetArray();
				std::vector<RenderEngine::Sprite::FrameDescription> frameDescriptions;
				frameDescriptions.reserve(framesArray.Size());

				for (const auto& currentFrame : framesArray)
				{
					const std::string subTextureStr = currentFrame["subTexture"].GetString();
					const uint64_t duration = currentFrame["duration"].GetUint64();
					const auto pTextureAtlas = getTexture(textureAtlas);
					const auto pSubTexture = pTextureAtlas->getSubTexture(subTextureStr);
					frameDescriptions.emplace_back(pSubTexture.leftBottomUV, pSubTexture.rightTopUV, duration);
				}

				pSprite->insertFrames(std::move(frameDescriptions));
			}
		}
	}

	// for parsing map data
	auto levelsIt = document.FindMember("levels");
	if (levelsIt != document.MemberEnd())
	{
		for (const auto& currentrLevel : levelsIt->value.GetArray())
		{
			const auto description = currentrLevel["description"].GetArray();
			std::vector<std::string> levelRows;
			levelRows.reserve(description.Size());
			size_t maxLenght = 0;
			for (const auto& currentRow : description)
			{
				levelRows.emplace_back(currentRow.GetString());
				maxLenght = std::max(maxLenght, levelRows.back().length());
			}

			for (auto& currentRow : levelRows)
			{
				while (currentRow.length() < maxLenght)
				{
					currentRow += "D";
				}
			}

			m_levels.emplace_back(std::move(levelRows));
		}
	}

	return true;
}