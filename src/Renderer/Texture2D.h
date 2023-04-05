#pragma once

#include <glm/vec2.hpp>
#include <glad/glad.h>
#include <map>
#include <string>


namespace Renderer
{
	class Texture2D
	{
	public:
		struct SubTexture2D
		{
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;

			SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV) 
				: leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV) {}

			SubTexture2D() 
				: leftBottomUV(0.f), rightTopUV(1.f) {}
		};

		Texture2D(const GLuint width, 
			const GLuint height,
			const unsigned char* data,
			const unsigned int channels,
			const GLenum filter,
			const GLenum wrapMode);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;

		Texture2D(Texture2D&& texture2d) noexcept;
		Texture2D& operator=(Texture2D&& texture2d) noexcept;
		~Texture2D() { glDeleteTextures(1, &m_ID); }

		void addSubTexture(std::string name, const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV);
		const SubTexture2D getSubTexture(const std::string& name) const;
		unsigned width() const { return m_width; }
		unsigned height() const { return m_height; }

		void bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); };

	private:
		GLuint m_ID;
		GLenum m_mode;
		unsigned m_width;
		unsigned m_height;
		std::map<std::string, SubTexture2D> m_subTextures;
	};
}