#include"../include/3DScene.h"

LightTestRoom *LightTestRoom::Instance = nullptr;

LightTestRoom::LightTestRoom(int width, int height, const char* title, bool screenmode, bool vsync)
{
    using namespace CustomSpace;

    Instance = this;
    m_Window = Windows::CreateWindow(WindowProps(width, height, title, screenmode, vsync));
    m_Window->SetEventCallback(BIND_EVENT(LightTestRoom::OnEvent));

    Renderer::Init();

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_Camera = CreateRef<OrthoCamera>(-width, width, -height, height);

    m_Camera->SetPosition(glm::vec3(0, 0, -1.f));
}

LightTestRoom::~LightTestRoom()
{
    delete Instance;
}


void LightTestRoom::Close()
{
    b_Running = false;
}

void LightTestRoom::Run()
{
    while(b_Running)
    {
        b_Running = !glfwWindowShouldClose((GLFWwindow*)m_Window->GetWindow());
        CustomSpace::RenderCommand::SetClearColor(glm::vec4(0.f, .3f, .65f, 1.f));
        CustomSpace::RenderCommand::Clear();

        CustomSpace::WindowProps& prop = *(CustomSpace::WindowProps*)glfwGetWindowUserPointer((GLFWwindow*)m_Window->GetWindow());

        // CORE_TRACE("width : {0} , height : {1}", prop.Width, prop.Height);
        CORE_TRACE("Mouse X : {0} , Mouse Y : {1}", CustomSpace::Input::MouseX, CustomSpace::Input::MouseY);

        m_Timer->CalculateTimer();

        m_Window->Update();
    }
}

void LightTestRoom::OnEvent(CustomSpace::Event& e)
{
    CustomSpace::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<CustomSpace::KeyPressedEvent>(BIND_EVENT(LightTestRoom::OnKeyPressedEvent));
}

bool LightTestRoom::OnKeyPressedEvent(CustomSpace::KeyPressedEvent& event)
{
    if(event.GetKeyCode() == GLFW_KEY_ESCAPE)
    {
        exit(EXIT_SUCCESS);
    }

    return false;
}
