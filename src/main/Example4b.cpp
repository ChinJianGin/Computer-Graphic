#include"../core/include/Core.h"
#include"../core/include/Input.h"
#include"../core/include/Window.h"
#include"../shader/ShaderClass.h"
#include"../vertex/VAO.h"
#include"../vertex/VBO.h"
#include"../vertex/EBO.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define DEGREETORADIUS M_PI/180.0

const int NumPoints = 6;

const char* WindowTitle = "Draw two colored triangles";

float angle = 0;
GLuint angleLoc;
glm::vec3 originalPoints[NumPoints];

glm::vec3 points[NumPoints] =
{
    glm::vec3(-.9f,  .9f, 0.f),
    glm::vec3( .9f,  .9f, 0.f),
    glm::vec3( .9f, -.9f, 0.f),
    glm::vec3(-.9f,  .9f, 0.f),
    glm::vec3( .9f, -.9f, 0.f),
    glm::vec3(-.9f, -.9f, 0.f)
};

glm::vec3 colors[NumPoints] =
{
    glm::vec3(1.f, 0.f, 0.f),
    glm::vec3(0.f, 1.f, 0.f),
    glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(1.f, 0.f, 0.f),
    glm::vec3(0.f, 0.f, 1.f),
    glm::vec3(1.f, 0.f, 1.f)
};

void GLFWErrorCallback(int Error, const char* Description)
{
	std::cout << "**GLFW ERROR Error : " << Error << "Description : " << Description << std::endl;
}



void init( void )
{
    for(int i = 0; i < NumPoints; i++) originalPoints[i] = points[i];
    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(sizeof(points) + sizeof(colors));
    VBO1.LoadRealData(0, sizeof(points), points);
    VBO1.LoadRealData(sizeof(points), sizeof(colors), colors);

    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 0, (void*)0);
    VAO1.LinkAttribute(VBO1, 1, 3, GL_FLOAT, 0, (void*)(sizeof(points)));
    VBO1.Bind();
}

void Display( void )
{
    glUniform1f(angleLoc, angle);
    angle += .1f;
    glDrawArrays(GL_TRIANGLES, 0, NumPoints);
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

    Shader ShaderProgram("../src/shader/Example4b.vert", "../src/shader/Example4b.frag");

    init();

    angleLoc = glGetUniformLocation(ShaderProgram.ID, "angle");

    while (!glfwWindowShouldClose(window->_Window))
    {
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();
        Display();
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit( EXIT_SUCCESS );

        glfwSwapBuffers(window->_Window);
        glfwPollEvents();
    }

    
    ShaderProgram.Delete();

    CustomSpace::Window::FreeWindow(window);
    glfwTerminate();
    return 0;

}