#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class cShader
{
public:
	//the program ID
	unsigned int m_uID;

	// Constructor reads and builds the shader
	cShader(const char* vertexPath, const char* fragmentPath)
	{
		// Retrieve the source code from the filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.what() << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// Compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// compile Fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// shader program
		m_uID = glCreateProgram();
		glAttachShader(m_uID, vertex);
		glAttachShader(m_uID, fragment);
		glLinkProgram(m_uID);
		glGetProgramiv(m_uID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_uID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// No longer needed since they have been linked into the program
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	~cShader() { glDeleteProgram(m_uID); }
	// Activate the shader
	void use()
	{
		glUseProgram(m_uID);
	}

	void setBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(m_uID, name.c_str()), (int)value);
	}
	void setInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(m_uID, name.c_str()), value);
	}
	void setFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(m_uID, name.c_str()), value);
	}

	void setVec2(const std::string& name, const glm::vec2& value) const
	{
		glUniform2fv(glGetUniformLocation(m_uID, name.c_str()), 1, &value[0]);
	}

	void setVec2(const std::string& name, float value1, float value2) const
	{
		glUniform2f(glGetUniformLocation(m_uID, name.c_str()), value1, value2);
	}

	void setVec3(const std::string& name, const glm::vec3& value) const
	{
		glUniform3fv(glGetUniformLocation(m_uID, name.c_str()), 1, &value[0]);
	}

	void setVec3(const std::string& name, float value1, float value2, float value3) const
	{
		glUniform3f(glGetUniformLocation(m_uID, name.c_str()), value1, value2, value3);
	}

	void setVec4(const std::string& name, const glm::vec4& value) const
	{
		glUniform4fv(glGetUniformLocation(m_uID, name.c_str()), 1, &value[0]);
	}

	void setVec4(const std::string& name, float value1, float value2, float value3, float value4) const
	{
		glUniform4f(glGetUniformLocation(m_uID, name.c_str()), value1, value2, value3, value4);
	}

	void setMat2(const std::string& name, const glm::mat2& value) const
	{
		glUniformMatrix2fv(glGetUniformLocation(m_uID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void setMat3(const std::string& name, const glm::mat3& value) const
	{
		glUniformMatrix3fv(glGetUniformLocation(m_uID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}

	void setMat4(const std::string& name, const glm::mat4& value) const
	{
		glUniformMatrix4fv(glGetUniformLocation(m_uID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
};
