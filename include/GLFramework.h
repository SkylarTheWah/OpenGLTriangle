#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma comment(lib, "../lib/glfw3.lib")


namespace GLFramework
{
	class GLApp
	{
	public:
		void Run();
		void setWindowX(int windowX);
		void setWindowY(int windowY);

	private:
		//the verticies for the triangle to be drawn
		const GLfloat _verticies[9] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		GLFWwindow* _window;

		//source for the ver and frag shaders
		const char* vertexShaderSource = "#version 330 core\n"
			"layout(location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
			"}\n";
		const char* fragmentShaderSource = "#version 330 core\n"
			"out vec4 FragColor;\n"
			"void main()\n"
			"{\n"
			"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
			"}\n";

		//objects
		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLuint VBO;
		GLuint VAO;

		int _windowX;
		int _windowY;

		bool Initialise();
		void CleanUp();
		void Render();
		void ProcessInput(GLFWwindow* window);
		void CreateObjects();
		void CreateShaders();
		void DestroyObjects();
		static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	};	
}