#include"Game.h"

ShootingGame* ShootingGame::Instance = nullptr;

ShootingGame::ShootingGame(int width, int height, const char* title, bool screen, bool vsync)
{
    using namespace CustomSpace;
    Instance = this;
    M_Window = Windows::CreateWindow(WindowProps(width, height, title, screen, vsync));

    //Renderer::Init();

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_Camera = CreateRef<OrthoCamera>(-2.f, 2.f, -2.f, 2.f);

    m_Camera->SetPosition(glm::vec3(0, 0, -.5f));
    CameraPosition = m_Camera->GetPosition();
    CameraRotation = m_Camera->GetRotation();

    //m_Triangle = CreateRef<Triangle>();
    /***
     * Create a shape progress
    ***/
    TriangleVAO = VAO::Create();

    glm::vec3 TrianglePoints[] = 
    {
        glm::vec3(-.5f, -.5f * float(sqrt(3)) / 3, 0.f),        glm::vec3(1.f, 0.f, 0.f),
        glm::vec3( .5f, -.5f * float(sqrt(3)) / 3, 0.f),        glm::vec3(.2f, .3f, .8f),
        glm::vec3( 0.f,  .5f * float(sqrt(3)) * 2 / 3, 0.f),    glm::vec3(.8f, .8f, .2f),
        glm::vec3( 0.f, -.5f * float(sqrt(3)) * 2 / 3, 0.f),    glm::vec3(.35f, .9f, .1f)
    };

    CustomSpace::Ref<VBO> TriangleVBO = VBO::Create(TrianglePoints, sizeof(TrianglePoints));

    CustomSpace::BufferLayout TriangleLayout = 
    {
        {CustomSpace::ShaderDataType::f_Vec3, "vPosition"},
        {CustomSpace::ShaderDataType::f_Vec3, "vColor"}
    };
    TriangleVBO->SetLayout(TriangleLayout);
    TriangleVAO->AddVBO(TriangleVBO);

    GLuint TriangleIndices[] =
    {
        0, 1, 2,
        0, 1, 3
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
        glClearColor(0.f, 1.f, .7f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Timer->CalculateTimer();

/***
 * Draw
***/
        TriangleShaderProgram->Activate();
        TriangleVAO->Bind();
        TriangleShaderProgram->SetMat4("uVP", m_Camera->GetVPMatrix());
        glDrawElements(GL_TRIANGLES, (TriangleVAO->GetEBO()->GetCount() / sizeof(GLuint)), GL_UNSIGNED_INT, 0);
///----------------------------------------
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_ESCAPE)) exit(EXIT_SUCCESS);
    
        CameraPosition = m_Camera->GetPosition();
        CameraRotation = m_Camera->GetRotation();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_A))
            CameraPosition.x -= (float)CameraMoveSpeed * m_Timer->GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_D))
            CameraPosition.x += (float)CameraMoveSpeed * m_Timer->GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_W))
            CameraPosition.y += (float)CameraMoveSpeed * m_Timer->GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_S))
            CameraPosition.y -= (float)CameraMoveSpeed * m_Timer->GetTick();

        m_Camera->SetPosition(CameraPosition);

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_E))
            CameraRotation += (float)CameraRotationSpeed * m_Timer->GetTick();
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_Q))
            CameraRotation -= (float)CameraRotationSpeed * m_Timer->GetTick();

        m_Camera->SetRotation(CameraRotation);

        M_Window->Update();        
    }
}