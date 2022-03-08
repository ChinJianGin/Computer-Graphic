#include "../include/Window.h"
#include "../include/WindowInstance.h"
#include "../include/Input.h"

namespace CustomSpace
{
    static void ResizeCallback(GLFWwindow* _Window, int NewWidth, int NewHeight)
    {
         Window* window = (Window*)glfwGetWindowUserPointer(_Window);
         window->WindowWidth = NewWidth;
         window->WindowHeight = NewHeight;
         glViewport(0, 0, NewWidth, NewHeight);
    }
    void Window::SetupMainCallbacks()
    {
        
        if(_Window != nullptr)
        {
            glfwSetKeyCallback(_Window, Input::KeyCallback);
            glfwSetCursorPosCallback(_Window, Input::MouseCallback);
            glfwSetMouseButtonCallback(_Window, Input::MouseButtonCallback);
            glfwSetWindowSizeCallback(_Window, ResizeCallback);
        }
    }

    void Window::Close()
    {
        if(_Window != nullptr)
        {
            glfwSetWindowShouldClose(_Window, GLFW_TRUE);
        }
    }

    Window* Window::CreateWindow(int Width, int Height, const char* Title, bool FullScreenMode)
    {
        // Tell GLFW what version of OpenGL we are using 
	    // In this case we are using OpenGL 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // Tell GLFW we are using the CORE profile
	    // So that means we only have the modern functions
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Only supply the monitor if we want to start the window in full-screen mode
        Window* Res = new Window();
        GLFWmonitor* PrimaryMonitor = FullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
        Res->_Window = glfwCreateWindow(Width, Height, Title, PrimaryMonitor, nullptr);
        if(Res->_Window == nullptr)
        {
            printf("Failed to create GLFW window\n");
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(Res->_Window);
        glfwSetWindowUserPointer(Res->_Window, (void*)Res);

        Res->WindowWidth = Width;
        Res->WindowHeight = Height;

        return Res;
    }

    void Window::FreeWindow(Window* window)
    {
        if(window)
        {
            glfwDestroyWindow(window->_Window);
            delete window;
        }
    }

    Scope<Windows> Windows::CreateWindow(const WindowProps& props)
    {
        return CreateScope<WindowInstance>(props);
    }
}