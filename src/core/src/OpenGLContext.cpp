#include"../include/OpenGLContext.h"

namespace CustomSpace
{
    OpenGLContext::OpenGLContext(GLFWwindow* window) : M_Window(window)
    {
        std::cout << "Create OpenGL Context" << std::endl;
    }

    Scope<OpenGLContext> OpenGLContext::Create(void* window)
    {
        return  CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(M_Window);
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD." << std::endl;
            glfwTerminate();
            return;
        }
    }
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(M_Window);
    }
}