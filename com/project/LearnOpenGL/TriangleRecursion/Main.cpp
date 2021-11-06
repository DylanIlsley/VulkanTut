#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "stb.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void RecursiveTriangle(unsigned int transformLoc, unsigned int customColourLoc, glm::vec3 translate, glm::mat4 transMatrix, int depth);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColour;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"	ourColour = aColor;\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColour;\n"
"uniform vec4 Fader;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColour, 1.0) * Fader;\n"
"}\n\0";

float fMixValue = 0.8f;
int iterations = 0;

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	cShader shaderProgram("..\\Shaders\\shader.vert", "..\\Shaders\\shader.frag");
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions          // colors           // texture coords
		 -1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f, // Point A top left
		 1.0f,   1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // Point B top right
		 0.0f,  -1.0f, 0.0f,   0.0f, 0.0f, 0.0f,   0.5f, 0.0f, // Point C bottom
		//0.0f,0.5f,0.0f, 0.0f, 0.0f, 1.0f //top
	};
	unsigned int indices[] = {
		// note that we start from 0!
		0,
		1,
		2
	};
	/*float texCoords[] = {
		0.0f, 0.0f, // lower left corner
		1.0f, 0.0f, // lower right corner
		0.5f, 1.0f // top center corner
	};*/

	// Loading textures
	// ----------------
	// TEXTURE 1
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	// setting the texture filtering options(on the currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Images/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load the texture" << std::endl;
	stbi_image_free(data);

	// TEXTURE 2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// setting the texture filtering options(on the currently bound texture object
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load and generate the texture
	width, height, nrChannels;
	data = stbi_load("Images/Psychi1.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
		std::cout << "Failed to load the texture" << std::endl;
	stbi_image_free(data);

	// Loading VBO, VAO, EBO
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// uncomment this call to draw in wireframe polygons.
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	shaderProgram.use();
	shaderProgram.setInt("texture1", 0);
	shaderProgram.setInt("texture2", 1);

	//shaderProgram.setFloat("faceAlpha", fMixValue);
	while (!glfwWindowShouldClose(window)) {
		// input
		// -----
		processInput(window);

		// render
		// ------
		glClearColor(0.1f, 0.07f, 0.07f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// be sure to activate the shader before any calls to glUniform
		shaderProgram.use();

		// Rotating box
		//unsigned int transformLoc = glGetUniformLocation(shaderProgram.m_uID, "transform");
		//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
	//	shaderProgram.setMat4("transform", trans);
		shaderProgram.setFloat("faceAlpha", fMixValue);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		// draw our first triangle
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		unsigned int transformLoc = glGetUniformLocation(shaderProgram.m_uID, "transform");
		unsigned int customColourLoc = glGetUniformLocation(shaderProgram.m_uID, "customColour");
		RecursiveTriangle(transformLoc, customColourLoc, glm::vec3(0.0f, -0.5f, 0.0f), glm::mat4(1.0f), 8);
		iterations++;
		// glm::
		// glBindVertexArray(0); // no need to unbind it every time

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		fMixValue += 0.01;
		if (fMixValue >= 1.0f)
			fMixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		fMixValue -= 0.01;
		if (fMixValue <= 0.0f)
			fMixValue = 0.0f;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void RecursiveTriangle(unsigned int transformLoc, unsigned int customColourLoc, glm::vec3 translate, glm::mat4 matrix, int depth)
{
	if (depth < 0)
		return;
	matrix = glm::translate(matrix, translate);
	matrix = glm::scale(matrix, glm::vec3(0.5f));

	auto tempMat = matrix;
	//if (depth % 2 == 1) {
	float iterFactor = iterations / 20.0f;// % 125 / 25.0f;
	glUniform3f(customColourLoc, abs((float)sin((glfwGetTime() + (8 - depth) + iterFactor) / 1.5)), abs(((float)sin(glfwGetTime() + (8 - depth) + iterFactor) / 2.5) + 0.1), abs(((float)sin((glfwGetTime() + (8 - depth) + iterFactor) / 3.5)) + 0.15));
	//tempMat = glm::rotate(tempMat, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, 0.0f));

//	}
		//auto rotMat = glm::mat4(1.0f);
	//	rotMat = glm::rotate(rotMat, (float)glfwGetTime(), glm::vec3(0.0f, 0.2f, 1.0f));
	//	tempMat = rotMat * tempMat;
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(tempMat));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

	--depth;
	RecursiveTriangle(transformLoc, customColourLoc, glm::vec3(0.0f, 1.5f, 0.0f), matrix, depth); //top
	RecursiveTriangle(transformLoc, customColourLoc, glm::vec3(-1.0f, -0.5f, 0.0f), matrix, depth); //left side
	matrix = glm::scale(matrix, glm::vec3(-1.0f, 1.0f, 1.0f));  // flip matrix on x to reverse our texture
	RecursiveTriangle(transformLoc, customColourLoc, glm::vec3(-1.0f, -0.5f, 0.0f), matrix, depth); //right side with same translatation since it was flipped
}