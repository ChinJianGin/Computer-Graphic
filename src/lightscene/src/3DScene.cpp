#include"../include/3DScene.h"

LightTestRoom *LightTestRoom::Instance = nullptr;

LightTestRoom::LightTestRoom(int width, int height, const char* title, bool screenmode, bool vsync)
{
    using namespace CustomSpace;

    Instance = this;
    m_Window = Windows::CreateWindow(WindowProps(width, height, title, screenmode, vsync));

    Renderer::Init();

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_Camera = CreateRef<OrthoCamera>(-width, width, -height, height);

    m_Camera->SetPosition(glm::vec3(0, 0, -1.f));
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

        m_Timer->CalculateTimer();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE))
            exit(EXIT_SUCCESS);

        m_Window->Update();
    }
}
