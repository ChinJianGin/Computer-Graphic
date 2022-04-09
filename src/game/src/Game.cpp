#include"Game.h"

ShootingGame* ShootingGame::Instance = nullptr;

ShootingGame::ShootingGame(int width, int height, const char* title, bool screen, bool vsync)
{
    using namespace CustomSpace;
    Instance = this;
    M_Window = Windows::CreateWindow(WindowProps(width, height, title, screen, vsync));

    Renderer::Init();

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_Camera = CreateRef<OrthoCamera>(-2.f, 2.f, -2.f, 2.f);

    m_Camera->SetPosition(glm::vec3(0, 0, -1.f));
    m_Rotation = 0;
    Transform = glm::vec3(0, 0, -1.f);
    Transform2 = glm::vec3(.5f, .5f, 0.f);

    m_Factory = CreateRef<ShapeFactory>();

    m_Triangle = m_Factory->ShapeCreator<Triangle>();
    m_Triangle_2 = m_Factory->ShapeCreator<Triangle>();
    m_Quad = m_Factory->ShapeCreator<Quad>();

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
        std::vector<glm::vec4> Color;
        m_Triangle_2->GetColor(Color);
        CustomSpace::Renderer::Submit(m_Triangle->GetVertexData()->m_Shader, m_Triangle);
        CustomSpace::Renderer::Submit(m_Triangle_2->GetVertexData()->m_Shader, m_Triangle_2);
        m_Quad->GetColor(Color);
        CustomSpace::Renderer::Submit(m_Quad->GetVertexData()->m_Shader, m_Quad);
        m_Quad->GetVertexData()->m_Shader->SetFloat4("uColor", Color[1]);
       ///----------------------------------------
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit(EXIT_SUCCESS);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_A))
            Transform.x -= (float)m_MoveSpeed * m_Timer->GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_D))
            Transform.x += (float)m_MoveSpeed * m_Timer->GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_W))
            Transform.y += (float)m_MoveSpeed * m_Timer->GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_S))
            Transform.y -= (float)m_MoveSpeed * m_Timer->GetTick();

        m_Triangle->SetPosition(Transform);
        m_Triangle_2->SetPosition(Transform2);
        m_Quad->SetPosition(Transform2 + glm::vec3(-1, -1, 0));
        // m_Camera->SetPosition(CameraPosition);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_E))
            m_Rotation -= (float)m_RotationSpeed * m_Timer->GetTick();
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_Q))
            m_Rotation += (float)m_RotationSpeed * m_Timer->GetTick();

        //m_Camera->SetRotation(CameraRotation);
        m_Triangle->SetRotation(m_Rotation, glm::vec3(1, 0, 1));

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_UP))
            m_Scale += (float)m_Timer->GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_DOWN))
            m_Scale -= (float)m_Timer->GetTick();
            
        m_Triangle->SetScale(m_Scale);
        M_Window->Update();        
    }
}