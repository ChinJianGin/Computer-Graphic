#include"../include/3DScene.h"
#include"../../light/DirectionLight.h"
#include"../../light/PointLight.h"
#include"../../light/SpotLight.h"

LightTestRoom *LightTestRoom::Instance = nullptr;

LightTestRoom::LightTestRoom(int width, int height, const char* title, bool screenmode, bool vsync)
{
    using namespace CustomSpace;

    Instance = this;
    m_Window = Windows::CreateWindow(WindowProps(width, height, title, screenmode, vsync));
    m_Window->SetEventCallback(BIND_EVENT(LightTestRoom::OnEvent));

    Renderer::Init();

    m_Factory = CreateScope<ShapeFactory>();

    m_Box = ShapeFactory::Get().ShapeCreator<Box>();
    m_Box->SetPosition(glm::vec3(0.f, 0.f, 0.f));
    m_Box->SetScale(glm::vec3(2.5f));
    glm::mat4 _MM = m_Box->GetTransform()->GetTranslate() * m_Box->GetTransform()->GetRotate() * m_Box->GetTransform()->GetScale();
    m_Box->SetModelMatrix(_MM);


    this->RoomInit();

    m_Pyramid = ShapeFactory::Get().ShapeCreator<Pyramid>();
    m_Pyramid->SetPosition(glm::vec3(0.f, 0.f, -1.f));
    // m_Pyramid->SetScale(glm::vec3(2.f, 2.f, 2.f));
    _MM = m_Pyramid->GetTransform()->GetTranslate() * m_Pyramid->GetTransform()->GetRotate() * m_Pyramid->GetTransform()->GetScale();
    m_Pyramid->SetModelMatrix(_MM);

    m_DirLight = CreateRef<DirectionLight>();
    // m_DirLight->SetAmbient(glm::vec3(.94f, .92f, .78f));
    m_DirLight->SetAmbient(glm::vec3(.01f, .01f, .01f));
    m_DirLight->SetDirection(glm::vec3(-.2f, 1.f, -.3f));
    m_DirLight->SetPosition(glm::vec3(1.f, 1.f, -1.f));
    _MM = m_DirLight->GetTransform()->GetTranslate();
    m_DirLight->SetModelMatrix(_MM);

    m_PointLight = CreateRef<PointLight>();
    auto _point = std::static_pointer_cast<PointLight>(m_PointLight);
    m_PointLight->SetAmbient(glm::vec3(.94f, .92f, .78f));
    m_PointLight->SetDiffuse(glm::vec3(.08f, .08f, .08f));
    m_PointLight->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
    m_PointLight->SetPosition(glm::vec3(.2f, .2f, 1.f));
    _MM = m_PointLight->GetTransform()->GetTranslate();
    m_PointLight->SetModelMatrix(_MM);

    m_SpotLight = CreateRef<SpotLight>();
    auto _spot = std::static_pointer_cast<SpotLight>(m_SpotLight);
    m_SpotLight->SetAmbient(glm::vec3(.0f, .5f, .0f));
    m_SpotLight->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight->SetPosition(glm::vec3(0.f, .5f, 0.f));
    m_SpotLight->SetDirection(glm::vec3(0.f, 0.f, -1.f));
    _MM = m_SpotLight->GetTransform()->GetTranslate();
    m_SpotLight->SetModelMatrix(_MM);

    m_StoneTex = Texture2D::Create("../src/TextureSrc/stone_wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_StoneSpec = Texture2D::Create("../src/TextureSrc/stone_wall_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_WoodTex = Texture2D::Create("../src/TextureSrc/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_WoodSpec = Texture2D::Create("../src/TextureSrc/wood_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_OrthoCamera = CreateRef<OrthoCamera>(width, height, -1.f, 1.f, -1.f, 1.f);

    m_OrthoCamera->SetPosition(glm::vec3(0.f, 0.f, -1.f));

    glm::vec3 CIP = glm::vec3(0.f);

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
        CustomSpace::RenderCommand::SetClearColor(glm::vec4(.2f, .2f, .2f, 1.f));
        CustomSpace::RenderCommand::Clear();

        CustomSpace::WindowProps& prop = *(CustomSpace::WindowProps*)glfwGetWindowUserPointer((GLFWwindow*)m_Window->GetWindow());

        m_Timer->CalculateTimer();
        m_AllTime += m_Timer->GetTick();

        CustomSpace::PerspectiveCamera* m_PersCamera = &m_PersController->GetCamera();
        CustomSpace::Renderer::BeginScene(m_PersController->GetCamera());
        CustomSpace::Renderer::BeginScene(*m_OrthoCamera);

        m_Interface->OnUpdate(*m_Timer);

        CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
        _shader->Activate();
        _shader->SetInt("HaveTex", true);
        _shader->SetInt("uMaterial.diffuse", 0);
        _shader->SetInt("uMaterial.specular", 1);
        _shader->SetFloat("uMaterial.shininess", 32.f);
        _shader->SetFloat3("uViewPos", m_PersController->GetCamera().GetPosition());
        this->LightControl();

        m_SpotLight->SetDirection(glm::vec3(glm::cos(m_AllTime), 0.f, glm::sin(m_AllTime)));

        this->RoomUpdate();

        m_StoneTex->Bind();
        m_StoneSpec->Bind();
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Pyramid->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(1), m_Pyramid);
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(1), m_Box);
        m_StoneTex->UnBind();
        m_StoneSpec->UnBind();

        m_ShaderPool->getShader(4)->Activate();
        m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(m_DirLight->GetLightData()->ambient, 1.0f));
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_DirLight->GetBody());
        m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(m_PointLight->GetLightData()->ambient, 1.0f));
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_PointLight->GetBody());
        m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(m_SpotLight->GetLightData()->ambient, 1.0f));
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_SpotLight->GetBody());


        m_ShaderPool->getShader(1)->Activate();
        m_ShaderPool->getShader(1)->SetMat4("uVP", m_PersController->GetCamera().GetVPMatrix());
        glm::mat4 model = glm::mat4(1.f);
        model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
        model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
        m_ShaderPool->getShader(1)->SetMat4("uMV", model);
        m_ShaderPool->getShader(1)->SetInt("HaveTex", true);
        m_ShaderPool->getShader(1)->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(model)));
        m_HeadCrab->Draw(*m_ShaderPool->getShader(1));

        model = glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 2.f));
        m_ShaderPool->getShader(1)->SetMat4("uMV", model);
        m_ShaderPool->getShader(1)->SetInt("HaveTex", true);
        m_ShaderPool->getShader(1)->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(model)));
        m_Crowbar->Draw(*m_ShaderPool->getShader(1));

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

void LightTestRoom::RoomInit()
{
    using namespace CustomSpace;

    glm::vec3 _scale = glm::vec3(2.5f, 1.f, 2.5f);
    glm::mat4 _MM(1.f);

    m_Ground = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Ground->SetPosition(glm::vec3(0.f, -.0001f, 0.f));
    m_Ground->SetScale(_scale);
    m_Ground->SetRotation(180.f);
    _MM = m_Ground->GetTransform()->GetTranslate() * m_Ground->GetTransform()->GetRotate() * m_Ground->GetTransform()->GetScale();
    m_Ground->SetModelMatrix(_MM);

    m_Ceiling = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Ceiling->SetPosition(glm::vec3(0.f, 5.0001f, 0.f));
    m_Ceiling->SetScale(_scale);
    // m_Ceiling->SetRotation(180.f);
    _MM = m_Ceiling->GetTransform()->GetTranslate() * m_Ceiling->GetTransform()->GetRotate() * m_Ceiling->GetTransform()->GetScale();
    m_Ceiling->SetModelMatrix(_MM);

    m_Wall[0] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[0]->SetPosition(glm::vec3(2.5f, 2.5f, 0.f));
    m_Wall[0]->SetScale(_scale);
    m_Wall[0]->SetRotation(-90.f);

    m_Wall[1] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[1]->SetPosition(glm::vec3(-2.5f, 2.5f, 0.f));
    m_Wall[1]->SetScale(_scale);
    m_Wall[1]->SetRotation(90.f);

    m_Wall[2] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[2]->SetPosition(glm::vec3(0.f, 2.5f, 2.5f));
    m_Wall[2]->SetScale(_scale);
    m_Wall[2]->SetRotation(90.f, glm::vec3(1.f, 0, 0));

    m_Wall[3] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[3]->SetPosition(glm::vec3(0.f, 2.5f, -2.5f));
    m_Wall[3]->SetScale(_scale);
    m_Wall[3]->SetRotation(90.f, glm::vec3(1.f, 0, 0));

    for(int i = 0; i < 4; i++)
    {
        if(i < 2)
        {
            _MM = m_Wall[i]->GetTransform()->GetTranslate() * glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(1.f, 0, 0)) * m_Wall[i]->GetTransform()->GetRotate() * m_Wall[i]->GetTransform()->GetScale();
        }
        else if(i == 2)
            _MM = m_Wall[i]->GetTransform()->GetTranslate() * m_Wall[i]->GetTransform()->GetRotate() * m_Wall[i]->GetTransform()->GetScale();
        else
            _MM = m_Wall[i]->GetTransform()->GetTranslate() * glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(0, 1.f, 0)) * m_Wall[i]->GetTransform()->GetRotate() * m_Wall[i]->GetTransform()->GetScale();
        m_Wall[i]->SetModelMatrix(_MM);
    }

    m_CeilingTex = Texture2D::Create("../src/TextureSrc/concreteceiling001a.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_WallTex[0] = Texture2D::Create("../src/TextureSrc/building_template015b.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_WallTex[1] = Texture2D::Create("../src/TextureSrc/building_template015f.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
}

void LightTestRoom::RoomUpdate()
{
    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
    m_WoodTex->Bind();
    m_WoodSpec->Bind();
    _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Ground->GetTransform()->GetModelMatrix())));
    CustomSpace::Renderer::Submit(_shader, m_Ground);
    m_WoodTex->UnBind();
    m_WoodSpec->UnBind();

    m_CeilingTex->Bind();
    _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Ceiling->GetTransform()->GetModelMatrix())));
    CustomSpace::Renderer::Submit(_shader, m_Ceiling);
    m_CeilingTex->UnBind();

    m_WallTex[1]->Bind();
    for(int i = 0; i < 3; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Wall[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_Wall[i]);
    }
    m_WallTex[1]->UnBind();

    m_WallTex[0]->Bind();
    _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Wall[3]->GetTransform()->GetModelMatrix())));
    CustomSpace::Renderer::Submit(_shader, m_Wall[3]);
    m_WallTex[0]->UnBind();
}

void LightTestRoom::LightControl()
{
    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
    _shader->SetInt("HaveDirLight", true);
    _shader->SetFloat3("uDirLight.direction", m_DirLight->GetLightData()->direction);
    _shader->SetFloat3("uDirLight.ambient", m_DirLight->GetLightData()->ambient);
    _shader->SetFloat3("uDirLight.diffuse", m_DirLight->GetLightData()->diffuse);
    _shader->SetFloat3("uDirLight.specular", m_DirLight->GetLightData()->specular);
    _shader->SetInt("HavePointLight", true);
    _shader->SetFloat3("uPointLight[0].position", m_PointLight->GetBody()->GetTransform()->GetLocalPosition());
    _shader->SetFloat3("uPointLight[0].ambient", m_PointLight->GetLightData()->ambient);
    _shader->SetFloat3("uPointLight[0].diffuse", m_PointLight->GetLightData()->diffuse);
    _shader->SetFloat3("uPointLight[0].specular", m_PointLight->GetLightData()->specular);
    auto _point = std::static_pointer_cast<CustomSpace::PointLight>(m_PointLight);
    _shader->SetFloat("uPointLight[0].constant", 1.f);
    _shader->SetFloat("uPointLight[0].linear", _point->GetLinear());
    _shader->SetFloat("uPointLight[0].quadratic", _point->GetQuadratic());
    _shader->SetInt("HaveSpotLight", true);
    _shader->SetFloat3("uSpotLight[0].position", m_SpotLight->GetTransform()->GetLocalPosition());
    _shader->SetFloat3("uSpotLight[0].direction", m_SpotLight->GetLightData()->direction);
    // _shader->SetFloat3("uSpotLight[0].position", m_PersController->GetCamera().GetPosition());
    // _shader->SetFloat3("uSpotLight[0].direction", m_PersController->GetCamera().GetLookAt());
    _shader->SetFloat3("uSpotLight[0].ambient", m_SpotLight->GetLightData()->ambient);
    _shader->SetFloat3("uSpotLight[0].diffuse", m_SpotLight->GetLightData()->diffuse);
    _shader->SetFloat3("uSpotLight[0].specular", m_SpotLight->GetLightData()->specular);
    auto _spot = std::static_pointer_cast<CustomSpace::SpotLight>(m_SpotLight);
    _shader->SetFloat("uSpotLight[0].constant", 1.f);
    _shader->SetFloat("uSpotLight[0].linear", _spot->GetLinear());
    _shader->SetFloat("uSpotLight[0].quadratic", _spot->GetQuadratic());
    _shader->SetFloat("uSpotLight[0].innerCutOff", _spot->GetInner());
    _shader->SetFloat("uSpotLight[0].outerCutOff", _spot->GetOuter());
}
