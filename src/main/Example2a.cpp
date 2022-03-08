#include"../core/include/Core.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define FPS 60

const int NumPoints = 6;

const char* WindowTitle = "Example 2";

int initial_time = 0, final_time = 0, frame_count = 0, count =0;

void GLFWErrorCallback(int Error, const char* Description)
{
	std::cout << "**GLFW ERROR Error : " << Error << "Description : " << Description << std::endl;
}

void init( VAO& VAO1 )
{
    using namespace glm;

    vec3 points[NumPoints] =
    {
        vec3(-.5f, -.5f * float(sqrt(3)) / 3, 0.f),
        vec3( .5f, -.5f * float(sqrt(3)) / 3, 0.f),
        vec3( .0f,  .5f * float(sqrt(3)) * 2 / 3, 0.f),
        vec3(-.5f / 2,  .5f * float(sqrt(3)) / 6, 0.f),
        vec3( .5f / 2,  .5f * float(sqrt(3)) / 6, 0.f),
        vec3( .0f, -.5f * float(sqrt(3)) / 3, 0.f)
    };

    GLuint indices[] = 
    {
        0, 3, 5,
        3, 5, 4
    };

    VAO1.Bind();

    VBO VBO1(points, sizeof(points));

    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkAttribute(VBO1, 0, 3, GL_FLOAT, 0, (void*)0);
    VAO1.UnBind();
    EBO1.UnBind();
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
    CoreTimer* TimerHandle = new CoreTimer(FPS);
    initial_time = TimerHandle->GetTick();
    window->SetupMainCallbacks();

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD." << std::endl;
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    Shader ShaderProgram("../src/shader/Example2.vert", "../src/shader/Example2.frag");

    VAO* VAO1 = new VAO;
    init(*VAO1);

    while (!glfwWindowShouldClose(window->_Window))
    {
        TimerHandle->CalculateTimer();
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear( GL_COLOR_BUFFER_BIT);
        ShaderProgram.Activate();

        VAO1->Bind();

        std::cout << "Tick : " << TimerHandle->GetTick() << "       ";
        std::cout << "DT : " << TimerHandle->GetDeltaTick() << std::endl;

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit( EXIT_SUCCESS );

        
        

        glfwSwapBuffers(window->_Window);
        glfwPollEvents();
    
        frame_count++;
        final_time = TimerHandle->GetTick();
        if(final_time - initial_time > 0)
        {
            std::cout << "FPS : " << frame_count / (final_time - initial_time) << std::endl;
            frame_count = 0;
            initial_time = final_time;
        }
        
    }

    
    ShaderProgram.Delete();

    CustomSpace::Window::FreeWindow(window);
    glfwTerminate();
    return 0;

}