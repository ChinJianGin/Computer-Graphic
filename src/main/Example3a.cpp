#include"../core/include/Core.h"
#include"../core/include/Input.h"
#include"../core/include/Window.h"
#include"../shader/ShaderClass.h"
#include"../vertex/VAO.h"
#include"../vertex/VBO.h"
#include"../vertex/EBO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define USING_STRIP 1

#ifndef USING_STRIP
const int NumPoints = 6;
#else
const int NumPoints = 4;
#endif

const char* WindowTitle = "Draw two colored triangles";

void GLFWErrorCallback(int Error, const char* Description)
{
	std::cout << "**GLFW ERROR Error : " << Error << "Description : " << Description << std::endl;
}

void init( void )
{
    using namespace CustomVector;
    #ifndef USING_STRIP
        Vector3_float points[NumPoints] = 
        {
            Vector3_float(-0.9f, -0.9f, 0.0),
            Vector3_float( 0.9f, -0.9f, 0.0),
            Vector3_float( 0.9f,  0.9f, 0.0),
            Vector3_float(-0.9f, -0.9f, 0.0),
            Vector3_float( 0.9f,  0.9f, 0.0),
            Vector3_float(-0.9f,  0.9f, 0.0)
        };
        Vector3_float colors[NumPoints] = 
        {
            Vector3_float(1.f, 0.f, 0.f),
            Vector3_float(0.f, 1.f, 0.f),
            Vector3_float(0.f, 0.f, 1.f),
            Vector3_float(1.f, 0.f, 0.f),
            Vector3_float(0.f, 0.f, 1.f),
            Vector3_float(1.f, 0.f, 1.f)
        };
    #else
        Vector3_float points[NumPoints] = 
        {
            Vector3_float(-0.9f,  0.9f, 0.0),
            Vector3_float(-0.9f, -0.9f, 0.0),
            Vector3_float( 0.9f,  0.9f, 0.0),
            Vector3_float( 0.9f, -0.9f, 0.0)
        };
        Vector3_float colors[NumPoints] = 
        {
            Vector3_float(1.f, 0.f, 0.f),
            Vector3_float(0.f, 1.f, 0.f),
            Vector3_float(0.f, 0.f, 1.f),
            Vector3_float(1.f, 0.f, 1.f)
        };
    #endif

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(sizeof(points) + sizeof(colors));
    VBO1.LoadRealData(0, sizeof(points), points);
    VBO1.LoadRealData(sizeof(points), sizeof(colors), colors);

    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 0, (void*)0);
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 0, (GLvoid*)(sizeof(points)));
    //VAO1.UnBind();
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

    Shader ShaderProgram("../src/shader/Example3a.vert", "../src/shader/Example3a.frag");

    init();

    while (!glfwWindowShouldClose(window->_Window))
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear( GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();
    #ifndef USING_STRIP
        glDrawArrays(GL_TRIANGLES, 0, NumPoints);
    #else
        glDrawArrays(GL_TRIANGLE_STRIP, 0, NumPoints);
    #endif

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit( EXIT_SUCCESS );

        glfwSwapBuffers(window->_Window);
        glfwPollEvents();
    }

    
    ShaderProgram.Delete();

    CustomSpace::Window::FreeWindow(window);
    glfwTerminate();
    return 0;

}