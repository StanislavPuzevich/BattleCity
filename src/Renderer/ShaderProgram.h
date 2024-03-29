#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <string>

namespace RenderEngine
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);

		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;

		ShaderProgram& operator =(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;
		~ShaderProgram() { glDeleteProgram(m_ID); }

		bool isCompiled() const { return m_isCompiled; }
		void use() const { glUseProgram(m_ID); }
		void setInt(const std::string& name, const GLint val);
		void setMatrix4(const std::string& name, const glm::mat4& matrix);

	private:
		bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		bool m_isCompiled = false;
		GLuint m_ID = 0;
	};
}