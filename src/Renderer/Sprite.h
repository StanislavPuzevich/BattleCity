#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

namespace Renderer
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Texture2D> pTexture,
			std::string initialSubTexture,
			std::shared_ptr<ShaderProgram> pShaderProgram,
			const glm::vec2& position = glm::vec2(0.f),
			const glm::vec2& size = glm::vec2(1.f),
			const float rotation = 0.f);

		Sprite (const Sprite&) = delete;
		Sprite& operator=(const Sprite&) = delete;

		virtual ~Sprite();

		virtual void render() const;
		void setPosition(const glm::vec2& position) { m_position = position; };
		void setSize(const glm::vec2& size) { m_size = size; };
		void setRotation(const float rotation) { m_rotation = rotation; };

	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		GLuint m_VAO;

		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_texturesCoordsBuffer;
		IndexBuffer m_indexBuffer;
	};
}