#include"../core/include/Core.h"
#include"../core/include/Input.h"
#include"../core/include/Window.h"
#include"../shader/ShaderClass.h"
#include"../vertex/VAO.h"
#include"../vertex/VBO.h"
#include"../vertex/EBO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define M_PI 3.14159265358979323846
#define RADIUS 0.8f
const int NumPoints = 500;
const char* WindowTitle = "Example 1";

CustomVector::Vector2_float points[NumPoints];

void GLFWErrorCallback(int Error, const char* Description)
{
	std::cout << "**GLFW ERROR Error : " << Error << "Description : " << Description << std::endl;
}

void init( void )
{
    for( int i = 0; i < NumPoints; i++)
    {
        points[i].x = RADIUS * cosf(M_PI * 2.f * i / NumPoints);
        points[i].y = RADIUS * sinf(M_PI * 2.f * i / NumPoints);
        std::cout << "X : " << points[i].x << " , " << "Y : " << points[i].y << std::endl;
    }
}



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

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    init();

    Shader ShaderProgram("../src/shader/Example1.vert", "../src/shader/Example1.frag");



    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(points, sizeof(points));

    
    VAO1.LinkAttribute(VBO1, 0, 2, GL_FLOAT, 0, (void*)0);
    VAO1.UnBind();

    while (!glfwWindowShouldClose(window->_Window))
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear( GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();

        VAO1.Bind();

        glDrawArrays(GL_POINTS, 0, NumPoints);
        glfwSwapBuffers(window->_Window);
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    ShaderProgram.Delete();

    CustomSpace::Window::FreeWindow(window);
    glfwTerminate();
    return 0;

}