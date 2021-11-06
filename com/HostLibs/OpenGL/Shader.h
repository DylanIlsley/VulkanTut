#pragma once
// -------------------------------
// SYSTEM INCLUDE FILES
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
// -------------------------------
// LIBRARY INCLUDE FILES
#include <glad/glad.h>
#include <glm/glm.hpp>
// -------------------------------
// LOCAL INCLUDE FILES

/// Class to handle shader programs
class cShader
{
public:
	//the program ID
	unsigned int m_uID; ///< The program ID

	/// Constructor reads and builds the shader
	/// @param[in] pVertexPath		Path to the vertex code
	/// @param[in] pFragmentPath	Path to the fragment code
	cShader(const char* pVertexPath, const char* pFragmentPath)
	{
		// Retrieve the source code from the filePath
		std::string strVertexCode;
		std::string strFragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			vShaderFile.open(pVertexPath);
			fShaderFile.open(pFragmentPath);

			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			strVertexCode = vShaderStream.str();
			strFragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e) {
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << e.what() << std::endl;
		}

		const char* vShaderCode = strVertexCode.c_str();
		const char* fShaderCode = strFragmentCode.c_str();

		// Compile shaders
		unsigned int uVertex, uFragment;
		int success;
		char infoLog[512];

		uVertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(uVertex, 1, &vShaderCode, NULL);
		glCompileShader(uVertex);

		glGetShaderiv(uVertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(uVertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// compile Fragment Shader
		uFragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(uFragment, 1, &fShaderCode, NULL);
		glCompileShader(uFragment);

		glGetShaderiv(uFragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(uFragment, 512, NULL, infoLog);
			std::cout << "ERROR:SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		}

		// shader program
		m_uID = glCreateProgram();
		glAttachShader(m_uID, uVertex);
		glAttachShader(m_uID, uFragment);
		glLinkProgram(m_uID);
		glGetProgramiv(m_uID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(m_uID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		}
		// No longer needed since they have been linked into the program
		glDeleteShader(uVertex);
		glDeleteShader(uFragment);
	}

	/// Destructor
	~cShader() { glDeleteProgram(m_uID); }

	/// Activate the shader
	void use()
	{
		glUseProgram(m_uID);
	}

	// Set functions to store values
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
