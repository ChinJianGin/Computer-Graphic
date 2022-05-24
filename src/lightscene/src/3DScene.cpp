#include"../include/3DScene.h"

LightTestRoom *LightTestRoom::Instance = nullptr;

LightTestRoom::LightTestRoom(int width, int height, const char* title, bool screenmode, bool vsync)
{
    using namespace CustomSpace;

    Instance = this;
    m_Window = Windows::CreateWindow(WindowProps(width, height, title, screenmode, vsync));
    m_Window->SetEventCallback(BIND_EVENT(LightTestRoom::OnEvent));

    Renderer::Init();

    m_Factory = CreateScope<ShapeFactory>();

    m_Triangle = ShapeFactory::Get().ShapeCreator<Triangle>();
    m_Triangle->SetPosition(glm::vec3(-1.6f, -.9f, 0.f));
    glm::mat4 _MM = m_Triangle->GetTransform()->GetTranslate() * m_Triangle->GetTransform()->GetRotate() * m_Triangle->GetTransform()->GetScale();
    m_Triangle->SetModelMatrix(_MM);

    m_Pyramid = ShapeFactory::Get().ShapeCreator<Pyramid>();
    m_Pyramid->SetPosition(glm::vec3(0.f, 0.f, -2.f));
    _MM = m_Pyramid->GetTransform()->GetTranslate();
    m_Pyramid->SetModelMatrix(_MM);

    m_LightBox = ShapeFactory::Get().ShapeCreator<Box>();
    m_LightBox->SetPosition(glm::vec3(1.f, 1.f, -3.f));
    _MM = m_LightBox->GetTransform()->GetTranslate();
    m_LightBox->SetModelMatrix(_MM);

    m_StoneTex = Texture2D::Create("../src/TextureSrc/stone_wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_OrthoCamera = CreateRef<OrthoCamera>(width, height, -1, 1, -1, 1);

    m_OrthoCamera->SetPosition(glm::vec3(0, 0, -1.f));

    glm::vec3 CIP = glm::vec3(0);

    m_PersController = CreateRef<PerspectiveCameraController>(width, height, 60.f, 1.f, 1000.f, CIP);

    m_CamPosition = m_PersController->GetCamera().GetPosition();

    m_ShaderPool = CreateScope<ShaderPool>();

    m_ShaderPool->getShader(0, "../src/shader/3DModel.vert", "../src/shader/3DModel.frag");
    m_ShaderPool->getShader(1, "../src/shader/LightMaterial.vert", "../src/shader/LightMaterial.frag");
    m_ShaderPool->getShader(2, "../src/shader/2DGameCircle.vert", "../src/shader/2DGameCircle.frag");
    m_ShaderPool->getShader(3, "../src/shader/2DGameTexture.vert", "../src/shader/2DGameTexture.frag");
    m_ShaderPool->getShader(4, "../src/shader/Light.vert", "../src/shader/Light.frag");

    m_HeadCrab = CustomSpace::CreateRef<CustomSpace::Model>("../src/Model/headcrab.obj");

    m_Crowbar = CustomSpace::CreateRef<CustomSpace::Model>("../src/Model/crowbar.obj");

    m_Interface = CreateScope<UserInterface>();
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
        CustomSpace::RenderCommand::SetClearColor(glm::vec4(0.f, 0.f, 0.f, 1.f));
        CustomSpace::RenderCommand::Clear();

        CustomSpace::WindowProps& prop = *(CustomSpace::WindowProps*)glfwGetWindowUserPointer((GLFWwindow*)m_Window->GetWindow());

        m_Timer->CalculateTimer();

        CustomSpace::PerspectiveCamera* m_PersCamera = &m_PersController->GetCamera();
        CustomSpace::Renderer::BeginScene(m_PersController->GetCamera());
        CustomSpace::Renderer::BeginScene(*m_OrthoCamera);

        m_Interface->OnUpdate(*m_Timer);

        m_StoneTex->Bind();
        m_ShaderPool->getShader(1)->Activate();
        m_ShaderPool->getShader(1)->SetInt("HaveTex", true);
        m_ShaderPool->getShader(1)->SetInt("tex0", 0);
        m_ShaderPool->getShader(1)->SetFloat3("lightColor", glm::vec4(1.f, 1.f, 1.f, 1.f));
        m_ShaderPool->getShader(1)->SetFloat3("lightPos", m_LightBox->GetTransform()->GetLocalPosition());
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(1), m_Pyramid);
        m_StoneTex->UnBind();

        m_ShaderPool->getShader(4)->Activate();
        m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(1.f, 1.f, 1.f, 1.f));
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_LightBox);


        m_ShaderPool->getShader(0)->Activate();
        m_ShaderPool->getShader(0)->SetMat4("uVP", m_PersController->GetCamera().GetVPMatrix());
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(2.f, 0.f, 2.f));
        m_ShaderPool->getShader(0)->SetMat4("uMV", model);
        m_HeadCrab->Draw(*m_ShaderPool->getShader(0));

        model = glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 2.f));
        m_ShaderPool->getShader(0)->SetMat4("uMV", model);
        m_Crowbar->Draw(*m_ShaderPool->getShader(0));

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_W))
        {
            m_CamPosition += m_PersCamera->GetLookAt() * glm::vec3(m_Timer->GetTick());
        }
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_S))
        {
            m_CamPosition += -m_PersCamera->GetLookAt() * glm::vec3(m_Timer->GetTick());
        }
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_A))
        {
            m_CamPosition += -glm::normalize(glm::cross(m_PersCamera->GetLookAt(), m_PersCamera->GetUp())) * glm::vec3(m_Timer->GetTick());
        }
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_D))
        {
            m_CamPosition += glm::normalize(glm::cross(m_PersCamera->GetLookAt(), m_PersCamera->GetUp())) * glm::vec3(m_Timer->GetTick());
        }
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_SPACE))
        {
            m_CamPosition += m_PersCamera->GetUp() * glm::vec3(m_Timer->GetTick());
        }
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_LEFT_CONTROL))
        {
            m_CamPosition += -m_PersCamera->GetUp() * glm::vec3(m_Timer->GetTick());
        }

        m_PersCamera->SetPosition(m_CamPosition);

        m_Window->Update();
    }
}

void LightTestRoom::OnEvent(CustomSpace::Event& e)
{
    CustomSpace::EventDispatcher dispatcher(e);
    dispatcher.Dispatch<CustomSpace::KeyPressedEvent>(BIND_EVENT(LightTestRoom::OnKeyPressedEvent));
    dispatcher.Dispatch<CustomSpace::WindowResizeEvent>(BIND_EVENT(LightTestRoom::OnWindowResizeEvent));

    m_Interface->OnEvent(e);
    if(!m_Interface->IsFocusOnInterface())
        m_PersController->OnEvent(e);
}

bool LightTestRoom::OnKeyPressedEvent(CustomSpace::KeyPressedEvent& event)
{
    if(event.GetKeyCode() == GLFW_KEY_ESCAPE)
    {
        exit(EXIT_SUCCESS);
    }

    return false;
}

bool LightTestRoom::OnWindowResizeEvent(CustomSpace::WindowResizeEvent& event)
{
    if(event.GetWidth() == 0 || event.GetHeight() == 0)
    {
        return false;
    }
    m_OrthoCamera->SetProjection(event.GetWidth(), event.GetHeight(), -1.f, 1.f, -1.f, 1.f);

    return false;
}
