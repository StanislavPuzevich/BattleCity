#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

constexpr GLuint BUFFER_SIZE = 1024;

namespace RenderEngine
{
	ShaderProgram::ShaderProgram(const std::string& vertex_shader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!CreateShader(vertex_shader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile-time error!" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile-time error!" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		// Creating a program for shaders 
		// Adding and linking these shaders together
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[BUFFER_SIZE];
			glGetShaderInfoLog(m_ID, BUFFER_SIZE, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link-time error:" << std::endl << infoLog << std::endl;
		}
		else
		{
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept
	{
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;

		return *this;
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept
	{
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;
	}

	void ShaderProgram::setInt(const std::string& name, const GLint val)
	{
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), val);
	}

	void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}

	bool ShaderProgram::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[BUFFER_SIZE];
			glGetShaderInfoLog(shaderID, BUFFER_SIZE, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error:" << std::endl << infoLog << std::endl;
			return false;
		}
		return true;
	}
}