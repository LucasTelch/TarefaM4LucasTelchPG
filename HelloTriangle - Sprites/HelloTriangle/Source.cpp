#include <iostream>
#include <string>
#include <assert.h>
#include<stb_image.h>

using namespace std;

#include "Shader.h"
#include "Sprite.h"

GLuint loadTexture(string texturePath);

const GLuint WIDTH = 800, HEIGHT = 600;

int main()
{
	glfwInit();

	srand((int)glfwGetTime());

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lucas Barreto Telch", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader shader("../shaders/tex.vs", "../shaders/tex.fs");

	GLuint texID = loadTexture("../../Textures/DesafioM4/fundo.png");
	GLuint texID2 = loadTexture("../../Textures/DesafioM4/fence.png");
	GLuint texID3 = loadTexture("../../Textures/DesafioM4/mago.png");
	GLuint texID4 = loadTexture("../../Textures/DesafioM4/ninja.png");
	GLuint texID5 = loadTexture("../../Textures/DesafioM4/ninja2.png");
	GLuint texID6 = loadTexture("../../Textures/DesafioM4/cavaleiro.png");

	Sprite fundo;
	fundo.setShader(&shader);
	fundo.inicializar(texID, glm::vec3(300.0, 300.0, 0.0), glm::vec3(1920.0/1.5, 1080.0/1.5, 1.0));

	Sprite fence;
	fence.setShader(&shader);
	fence.inicializar(texID2, glm::vec3(300.0, 300.0, 0.0), glm::vec3(1920.0 /1.5, 1080.0/ 1.5, 1.0));

	Sprite mago;
	mago.setShader(&shader);
	mago.inicializar(texID3, glm::vec3(200.0, 100.0, 0.0), glm::vec3(128.0, 128.0, 1.0));

	Sprite ninja;
	ninja.setShader(&shader);
	ninja.inicializar(texID4, glm::vec3(300.0, 100.0, 0.0), glm::vec3(128.0, 128.0, 1.0));

	Sprite ninja2;
	ninja2.setShader(&shader);
	ninja2.inicializar(texID5, glm::vec3(400.0, 100.0, 0.0), glm::vec3(128.0, 128.0, 1.0));

	Sprite cavaleiro;
	cavaleiro.setShader(&shader);
	cavaleiro.inicializar(texID6, glm::vec3(500.0, 100.0, 0.0), glm::vec3(128.0, 128.0, 1.0));

	glActiveTexture(GL_TEXTURE0);

	shader.Use();

	glm::mat4 projection = glm::ortho(0.0,800.0,0.0,600.0,-1.0,1.0);
	shader.setMat4("projection", glm::value_ptr(projection));
	
	shader.setInt("texBuffer", 0);

	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);
		
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		fundo.desenhar();
		fence.desenhar();
		mago.desenhar();
		ninja.desenhar();
		ninja2.desenhar();
		cavaleiro.desenhar();

		glfwSwapBuffers(window);
	}
	
	glfwTerminate();
	return 0;
}

GLuint loadTexture(string texturePath)
{
	GLuint texID;

	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

