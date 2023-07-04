#pragma once

#include "Sprite.h"

#include <map>
#include <vector>

namespace RenderEngine
{
	class AnimatedSprite: public Sprite
	{
	public:
		AnimatedSprite(std::shared_ptr<Texture2D> pTexture, std::string initialSubTexture, std::shared_ptr<ShaderProgram> pShaderProgram);

		void insertState(std::string state, std::vector<std::pair<std::string, uint64_t>> subTexturesDuration)
			{ m_statesMap.emplace(std::move(state), std::move(subTexturesDuration)); }
		void render(const glm::vec2& position, const glm::vec2& size, const float rotation) const override;
		void setState(const std::string& newState);
		void update(const uint64_t delta);

	private:
		//this data structure store "State name" like string and "Subtexture name" + "Duration" like pairs of vector
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>> m_statesMap;
		size_t m_currentFrame = 0;
		uint64_t m_currentAnimationTime = 0;
		std::map<std::string, std::vector<std::pair<std::string, uint64_t>>>::const_iterator m_pCurrentAnimationDurations;
		mutable bool m_dirty = false;
	};
}