#pragma once

#include <glad/glad.h>

namespace Renderer
{
	class Texture2D
	{
	public:
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

		void bind() const { glBindTexture(GL_TEXTURE_2D, m_ID); };

	private:
		GLuint m_ID = 0;
		GLenum m_mode = 0;
		unsigned int m_width = 0;
		unsigned m_height = 0;
	};
}