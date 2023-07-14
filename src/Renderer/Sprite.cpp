#include "Sprite.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RenderEngine
{
	Sprite::Sprite(std::shared_ptr<Texture2D> pTexture, std::string initialSubTexture, std::shared_ptr<ShaderProgram> pShaderProgram)
		: m_pTexture(std::move(pTexture)), m_pShaderProgram(std::move(pShaderProgram)), m_lastFrameID(0)
	{
		const GLfloat vertexCoords[] = {
			// 1---2    
			// | / |
			// 0---3

			//X  Y
			0.f,0.f,
			0.f,1.f,
			1.f,1.f,
			1.f,0.f,
		};

		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		const GLfloat textureCoords[] = {
			//U  V
			subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
			subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.rightTopUV.y,
			subTexture.rightTopUV.x, subTexture.leftBottomUV.y,
		};

		const GLint indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m_vertexCoordsBuffer.init(vertexCoords, sizeof(vertexCoords));
		VertexBufferLayout vertexCoordsLyout;
		vertexCoordsLyout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_vertexCoordsBuffer, vertexCoordsLyout);

		m_textureCoordsBuffer.init(textureCoords, sizeof(textureCoords));
		VertexBufferLayout texturesCoordsLyout;
		texturesCoordsLyout.addElementLayoutFloat(2, false);
		m_vertexArray.addBuffer(m_textureCoordsBuffer, texturesCoordsLyout);

		m_indexBuffer.init(indices, 6);

		m_vertexArray.unbind();
		m_indexBuffer.unbind();
	}

	void Sprite::render(const glm::vec2& position, const glm::vec2& size, const float rotation, const size_t frameID) const
	{
		if (m_lastFrameID != frameID)
		{
			m_lastFrameID = frameID;
			const FrameDescription& currentFrameDescriotion = m_framesDescriptions[frameID];

			const GLfloat textureCoords[] = {
				//U  V
				currentFrameDescriotion.leftBottomUV.x, currentFrameDescriotion.leftBottomUV.y,
				currentFrameDescriotion.leftBottomUV.x, currentFrameDescriotion.rightTopUV.y,
				currentFrameDescriotion.rightTopUV.x,   currentFrameDescriotion.rightTopUV.y,
				currentFrameDescriotion.rightTopUV.x,   currentFrameDescriotion.leftBottomUV.y,
			};

			m_textureCoordsBuffer.update(textureCoords, sizeof(textureCoords));
			m_textureCoordsBuffer.unbind();
		}

		m_pShaderProgram->use();

		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
		model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
		model = glm::scale(model, glm::vec3(size, 1.f));

		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		m_pTexture->bind();

		Renderer::draw(m_vertexArray, m_indexBuffer, *m_pShaderProgram);
	}
}