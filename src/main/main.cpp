#include"../core/include/Core.h"
#include"../core/include/Input.h"
#include"../core/include/Window.h"
#include"../shader/ShaderClass.h"
#include"../vertex/VAO.h"
#include"../vertex/VBO.h"
#include"../vertex/EBO.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
const char* WindowTitle = "OpenGL";

void GLFWErrorCallback(int Error, const char* Description)
{
	std::cout << "**GLFW ERROR Error : " << Error << "Description : " << Description << std::endl;
}

// Vertices coordinates
GLfloat vertices[] =
{
	-.5f, -.5f * float(sqrt(3)) / 3, 0.0f, 0.8f, 0.3f, 0.02f,// Lower left corner
	.5f, -.5f * float(sqrt(3)) / 3, 0.0f, 0.3f, 1.0f, 0.5f,// Lower right corner
	-.5f, .5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.6f, 0.32f,// Upper corner
	-0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 1.0f, 1.0f,
	0.25f, 0.5f * float(sqrt(3)) / 6, 0.0f, 0.0f, 0.0f, 1.0f,
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f, 1.0f, 0.0f, 1.0f,
	0.5f, .5f * float(sqrt(3)) * 2 / 3, 0.0f, 1.0f, 0.0f, 1.0f
};

GLuint indices[] =
{
	0, 1, 2,
	2, 6, 1
};


int main()
{
	glfwSetErrorCallback(GLFWErrorCallback);
	// Initialize GLFW
	if(!glfwInit())
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		return -1;
	}

	CustomSpace::Window* window = CustomSpace::Window::CreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WindowTitle);

	if(window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	window->SetupMainCallbacks();

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD." << std::endl;
		glfwTerminate();
		return -1;
	}

	

	// // Tell GLFW what version of OpenGL we are using 
	// // In this case we are using OpenGL 3.3
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	// glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// // Tell GLFW we are using the CORE profile
	// // So that means we only have the modern functions
	// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// // Create a GLFWwindow object of 800 by 800 pixels, naming it "OpenGL"
	// GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
	// // Error check if the window fails to create
	// if (window == NULL)
	// {
	// 	std::cout << "Failed to create GLFW window" << std::endl;
	// 	glfwTerminate();
	// 	return -1;
	// }
	// // Introduce the window into the current context
	// glfwMakeContextCurrent(window);

	// //Load GLAD so it configures OpenGL
	// gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);



	Shader ShaderProgram("../src/shader/default.vert", "../src/shader/default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));

	EBO EBO1(indices, sizeof(indices));

	VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO1.UnBind();
	VBO1.UnBind();
	EBO1.UnBind();

	GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");

	// Main while loop
	while (!glfwWindowShouldClose(window->_Window))
	{
		// Specify the color of the background
		glClearColor(0.05f, 0.33f, 0.15, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
		ShaderProgram.Activate();
		glUniform1f(uniID, 0.5f);
		// Bind the VAO so OpenGL knows to use it
		VAO1.Bind();
		// Draw the triangle using the GL_TRIANGLES primitive
		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window->_Window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	ShaderProgram.Delete();
	// Delete window before ending the program
	//glfwDestroyWindow(window);
	CustomSpace::Window::FreeWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}