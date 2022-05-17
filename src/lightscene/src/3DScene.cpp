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

    m_Triangle = m_Factory->ShapeCreator<Triangle>();
    m_Triangle->SetPosition(glm::vec3(-.5f, -.5f, 0.f));
    glm::mat4 _MM = m_Triangle->GetTransform()->GetTranslate() * m_Triangle->GetTransform()->GetRotate() * m_Triangle->GetTransform()->GetScale();
    m_Triangle->SetModelMatrix(_MM);

    m_Pyramid = m_Factory->ShapeCreator<Pyramid>();
    _MM = m_Pyramid->GetTransform()->GetTranslate();
    m_Pyramid->SetModelMatrix(_MM);

    m_StoneTex = Texture2D::Create("../src/TextureSrc/stone_wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_OrthoCamera = CreateRef<OrthoCamera>(width, height, -1, 1, -1, 1);

    m_OrthoCamera->SetPosition(glm::vec3(0, 0, -1.f));

    glm::vec3 CIP = glm::vec3(0);

    m_PersController = CreateRef<PerspectiveCameraController>(width, height, 60.f, 1.f, 1000.f, CIP);

    m_CamPosition = m_PersController->GetCamera().GetPosition();

    m_ModelShader = CustomSpace::CreateRef<Shader>("../src/shader/3DModel.vert", "../src/shader/3DModel.frag");

    m_HeadCrab = CustomSpace::CreateRef<CustomSpace::Model>("../src/Model/headcrab_noskeleton.obj");
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
        // CORE_TRACE("Mouse X : {0} , Mouse Y : {1}", CustomSpace::Input::MouseX, CustomSpace::Input::MouseY);

        m_Timer->CalculateTimer();

        // CustomSpace::Renderer::BeginScene(*m_OrthoCamera);
        CustomSpace::PerspectiveCamera* m_PersCamera = &m_PersController->GetCamera();
        CustomSpace::Renderer::BeginScene(m_PersController->GetCamera());
        CustomSpace::Renderer::BeginScene(*m_OrthoCamera);

        m_StoneTex->Bind();
        CustomSpace::Renderer::Submit(m_Pyramid->GetVertexData()->m_Shader, m_Pyramid);
        m_Pyramid->GetVertexData()->m_Shader->SetInt("tex0", 0);
        m_StoneTex->UnBind();

        CustomSpace::Render2D::RenderTarget(m_Triangle->GetVertexData()->m_Shader, m_Triangle);

        m_ModelShader->Activate();
        m_ModelShader->SetMat4("uVP", m_PersController->GetCamera().GetVPMatrix());
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f));
        model = glm::scale(model, glm::vec3(.05f));
        m_ModelShader->SetMat4("uMV", model);
        m_HeadCrab->Draw(*m_ModelShader);

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

    CORE_TRACE("Resize event");
    // CustomSpace::Renderer::
    return false;
}
