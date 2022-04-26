#include"../include/Game.h"

ShootingGame* ShootingGame::Instance = nullptr;

ShootingGame::ShootingGame(int width, int height, const char* title, bool screen, bool vsync)
{
    using namespace CustomSpace;
    Instance = this;
    M_Window = Windows::CreateWindow(WindowProps(width, height, title, screen, vsync));
    M_Window->SetEventCallback(BIND_EVENT(ShootingGame::OnEvent));

    Renderer::Init();

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_Camera = CreateRef<OrthoCamera>(-2.4f, 2.4f, -4.8f, 4.8f);

    m_Camera->SetPosition(glm::vec3(0, 0, -1.f));
    m_Rotation = 0;
    m_Transform = glm::vec3(0, 0, -0.5f);
    m_Transform2 = glm::vec3(1.f, 1.f, -1.f);

    m_Factory = CreateRef<ShapeFactory>();

    m_Scene1 = CreateRef<Scene>();
        
    CORE_WARN("Shooting game constructor done");
}

void ShootingGame::Close()
{
    B_Running =  false;
}

void ShootingGame::Run()
{
    while(B_Running)
    {
        B_Running = !glfwWindowShouldClose((GLFWwindow*)M_Window->GetWindow());
        CustomSpace::RenderCommand::SetClearColor(glm::vec4(0.f, 1.f, .7f, 1.f));
        CustomSpace::RenderCommand::Clear();        

        m_Timer->CalculateTimer();

/***
 * Draw
***/
        CustomSpace::Renderer::BeginScene(*m_Camera);
        
        m_Scene1->Update(*m_Timer);
       ///----------------------------------------

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit(EXIT_SUCCESS);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_A))
            m_Transform.x -= (float)m_MoveSpeed * m_Timer->GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_D))
            m_Transform.x += (float)m_MoveSpeed * m_Timer->GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_W))
            m_Transform.y += (float)m_MoveSpeed * m_Timer->GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_S))
            m_Transform.y -= (float)m_MoveSpeed * m_Timer->GetTick();

        // m_Camera->SetPosition(CameraPosition);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_E))
            m_Rotation -= (float)m_RotationSpeed * m_Timer->GetTick();
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_Q))
            m_Rotation += (float)m_RotationSpeed * m_Timer->GetTick();

        //m_Camera->SetRotation(CameraRotation);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_UP))
            m_Scale += (float)m_Timer->GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_DOWN))
            m_Scale -= (float)m_Timer->GetTick();
            

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_R))
        {
            m_Transform = OriginTrans->m_Position;
            m_Rotation = OriginTrans->m_Rotation;
            // m_Scale = OriginTrans->m_Scale;
        }    

        M_Window->Update();        
    }
}


void ShootingGame::OnEvent(CustomSpace::Event& e)
{
    CustomSpace::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<CustomSpace::KeyPressedEvent>(BIND_EVENT(ShootingGame::OnKeyPressedEvent));
}

bool ShootingGame::OnKeyPressedEvent(CustomSpace::KeyPressedEvent& event)
{
    if(event.GetKeyCode() == GLFW_KEY_1)
    {
        CORE_INFO("One event pressed");
    }

    return false;
}