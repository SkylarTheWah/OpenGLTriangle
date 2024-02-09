#include <iostream>
#include "GLFramework.h"

#ifndef DEBUG
#define DEBUG 1
#endif

#include "DebugPrint.h"

namespace GLFramework
{
	// *************************
	// * BEGIN PRIVATE METHODS *
	// *************************
	bool GLApp::Initialise()
	{
		//initialise OpenGL
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//now create the window
		_window = glfwCreateWindow(_windowX, _windowY, "HelloOpenGL", NULL, NULL);
		if (_window == NULL)
		{
			DEBUG_PRINT("Failed to create GLFW Window :(");
			glfwTerminate();
			return false;
		}
		DEBUG_PRINT("GLFW window successfully created!");

		glfwMakeContextCurrent(_window);

		//now initialise GLAD
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			DEBUG_PRINT("Failed to initialise GLAD :(");
			return false;
		}
		DEBUG_PRINT("GLAD initialised!");
		return true;
	}

	void GLApp::CleanUp()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
	}

	void GLApp::Render()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// use compiled shader program for rendering
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void GLApp::ProcessInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void GLApp::CreateObjects()
	{
		//triangle verticies. x, y, z
		GLfloat verticies[9] =
		{
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		//generate buffers for VBO
		glGenBuffers(1, &VBO);

		//do same for VAO
		glGenVertexArrays(1, &VAO);

		//now create the shaders
		GLApp::CreateShaders();

		//bind the vao
		glBindVertexArray(VAO);

		//copy triangle verts into the vbo
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

		//set attribs pointers
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//now enable vao
		glEnableVertexAttribArray(0);
	}

	void GLApp::CreateShaders()
	{
		//VERTEX SHADER
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success;
		GLchar infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			DEBUG_PRINT("ERROR!! Unable to compile vertex shader");
			DEBUG_PRINT(infoLog);
		}

		//FRAGMENT SHADER
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			DEBUG_PRINT("ERROR!! Unable to compile fragment shader");
			DEBUG_PRINT(infoLog);
		}
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			DEBUG_PRINT("ERROR!! Unable to link shader program");
			DEBUG_PRINT(infoLog);
		}
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void GLApp::DestroyObjects()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteProgram(shaderProgram);
	}

	void GLApp::framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	// ************************
	// * BEGIN PUBLIC METHODS *
	// ************************
	void GLApp::Run()
	{
		//initialise our GL app
		GLApp::Initialise();

		//set viewport dimentions
		glViewport(0, 0, _windowX, _windowY);

		//register callback
		glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

		//create our objects - the VBO and VAO
		GLApp::CreateObjects();

		// *******************************************
		// * HERE BE WHERE THE RENDER LOOP BEGINS!!! *
		// *******************************************
		while (!glfwWindowShouldClose(_window))
		{
			//process any user input - monitoring for esc to close app
			GLApp::ProcessInput(_window);

			//do rendering
			GLApp::Render();

			//poll events then swap the buffers
			glfwPollEvents();
			glfwSwapBuffers(_window);
		}
		//destroy objects in memory then terminate glfw
		GLApp::DestroyObjects();
		glfwTerminate();
	}

	void GLApp::setWindowX(int windowX)
	{
		_windowX = windowX;
	}

	void GLApp::setWindowY(int windowY)
	{
		_windowY = windowY;
	}
}
