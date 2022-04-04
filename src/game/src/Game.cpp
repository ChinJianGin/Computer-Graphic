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

    m_Camera->SetPosition(glm::vec3(0, 0, -.5f));
    m_Rotation = 0;
    Transform = glm::vec3(0);

    m_Triangle = CreateRef<Triangle>();
    /***
     * Create a shape progress
    ***/
    TriangleVAO = VAO::Create();

    // glm::vec3 TrianglePoints[] = 
    // {
    //     glm::vec3(-.5f, -.5f * float(sqrt(3)) / 3, 0.f),        glm::vec3(1.f, 0.f, 0.f),
    //     glm::vec3( .5f, -.5f * float(sqrt(3)) / 3, 0.f),        glm::vec3(.2f, .3f, .8f),
    //     glm::vec3( 0.f,  .5f * float(sqrt(3)) * 2 / 3, 0.f),    glm::vec3(.8f, .8f, .2f),
    //     glm::vec3( 0.f, -.5f * float(sqrt(3)) * 2 / 3, 0.f),    glm::vec3(.35f, .9f, .1f)
    // };

    //CustomSpace::Ref<VBO> TriangleVBO = VBO::Create(TrianglePoints, sizeof(TrianglePoints));
    glm::vec3 Points[m_Triangle->GetPointsData()->Points.size()];
    std::copy(m_Triangle->GetPointsData()->Points.begin(), m_Triangle->GetPointsData()->Points.end(), Points);

    CustomSpace::Ref<VBO> TriangleVBO = VBO::Create(&(m_Triangle->GetPointsData()->Points.front()), sizeof(glm::vec3) * m_Triangle->GetPointsData()->Points.size());
    CustomSpace::BufferLayout TriangleLayout = 
    {
        {CustomSpace::ShaderDataType::f_Vec3, "vPosition"},
        {CustomSpace::ShaderDataType::f_Vec3, "vColor"}
    };
    TriangleVBO->SetLayout(TriangleLayout);
    TriangleVAO->AddVBO(TriangleVBO);

    GLuint TriangleIndices[] =
    {
        0, 1, 2
    };

    CustomSpace::Ref<EBO> TriangleEBO = EBO::Create(TriangleIndices, sizeof(TriangleIndices));
    TriangleVAO->SetEBO(TriangleEBO);
    //----------------------------------------------------


    
    TriangleShaderProgram = CustomSpace::CreateRef<Shader>(Shader("../src/shader/2DGame.vert", "../src/shader/2DGame.frag"));
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
        TriangleShaderProgram->Activate();
        TriangleVAO->Bind();
        TriangleShaderProgram->SetMat4("uMV", m_Triangle->GetTransform()->m_ModelMatrix);
        TriangleShaderProgram->SetMat4("uVP", m_Camera->GetVPMatrix());
        glDrawElements(GL_TRIANGLES, (TriangleVAO->GetEBO()->GetCount() / sizeof(GLuint)), GL_UNSIGNED_INT, 0);
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
        //m_Camera->SetPosition(CameraPosition);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_E))
            m_Rotation -= (float)m_RotationSpeed * m_Timer->GetTick();
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_Q))
            m_Rotation += (float)m_RotationSpeed * m_Timer->GetTick();

        //m_Camera->SetRotation(CameraRotation);
        m_Triangle->SetRotation(m_Rotation);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_UP))
            m_Scale += (float)m_Timer->GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_DOWN))
            m_Scale -= (float)m_Timer->GetTick();
            
        m_Triangle->SetScale(m_Scale);
        M_Window->Update();        
    }
}