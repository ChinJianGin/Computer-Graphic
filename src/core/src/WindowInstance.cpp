#include"../include/WindowInstance.h"
#include"../include/WindowEvent.h"

namespace CustomSpace
{
    static void GLFWErrorCallback(int Error, const char* Description)
    {
        std::cout << "**GLFW ERROR Error : " << Error << "Description : " << Description << std::endl;
    }
    static void ResizeCallback(GLFWwindow* _Window, int NewWidth, int NewHeight)
    {
        WindowProps& window = *(WindowProps*)glfwGetWindowUserPointer(_Window);
        window.Width = NewWidth;
        window.Height = NewHeight;

        WindowResizeEvent event(NewWidth, NewHeight);
        window.EventCallback(event);
    }
    static void FrameBufferResizeCallback(GLFWwindow* _Window, int NewWidth, int NewHeight)
    {
        glViewport(0, 0, NewWidth, NewHeight);
    }
    WindowInstance::WindowInstance(const WindowProps& props)
    {
        this->Init(props);
    }

    WindowInstance::~WindowInstance()
    {
        this->Shutdown();
    }

    void WindowInstance::Init(const WindowProps& props)
    {
        M_Prop = props;

        if(!glfwInit())
        {
            std::cout << "GLFW failed to initialize" << std::endl;
            return;
        }

        glfwSetErrorCallback(GLFWErrorCallback);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        GLFWmonitor* PrimaryMonitor = props.FullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
        M_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title, PrimaryMonitor, nullptr);

        if(M_Window == nullptr)
        {
            printf("Failed to create GLFW window\n");
            glfwTerminate();
            return;
        }

        M_Context = OpenGLContext::Create(M_Window);
        M_Context->Init();
        glEnable(GL_DEPTH_TEST);

        int screenWidth, screenHeight;
        glfwGetFramebufferSize(M_Window, &screenWidth, &screenHeight);
        glViewport(0, 0, screenWidth, screenHeight);

        glfwSetWindowUserPointer(M_Window, &M_Prop);

        SetVSync(false);

        this->SetupMainCallbacks();
    }

    void WindowInstance::SetupMainCallbacks()
    {
        if(M_Window != nullptr)
        {
            glfwSetKeyCallback(M_Window, Input::KeyCallback);
            glfwSetCursorPosCallback(M_Window, Input::MousePosCallback);
            glfwSetMouseButtonCallback(M_Window, Input::MouseButtonCallback);
            glfwSetWindowSizeCallback(M_Window, ResizeCallback);
            glfwSetFramebufferSizeCallback(M_Window, FrameBufferResizeCallback);
        }
    }

    void WindowInstance::Shutdown()
    {
        glfwDestroyWindow(M_Window);
        glfwTerminate();
    }

    void WindowInstance::Update()
    {
        glfwPollEvents();
        M_Context->SwapBuffers();
    }

    void WindowInstance::SetVSync(bool enable)
    {
        if(enable) glfwSwapInterval(1);
        else glfwSwapInterval(0);

        M_Prop.VSync = enable;
    }

    bool WindowInstance::IsVSync() const
    {
        return M_Prop.VSync;
    }
}