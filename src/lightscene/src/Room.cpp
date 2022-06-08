#include"../include/Room.h"
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

    this->Init();

    m_Skybox = CreateRef<Skybox>();

    m_Timer = CreateScope<CoreTimer>(TARGET_FRAMERATE);

    m_OrthoCamera = CreateRef<OrthoCamera>(width, height, -1.f, 1.f, -1.f, 1.f);

    m_OrthoCamera->SetPosition(glm::vec3(0.f, 0.f, -1.f));

    glm::vec3 CIP = glm::vec3(0.f);

    m_PersController = CreateRef<PerspectiveCameraController>(width, height, 60.f, .1f, 1000.f, CIP);

    m_PersController->GetCamera().SetPosition(glm::vec3(0.f, 2.5f, 0.f));

    m_CamPosition = m_PersController->GetCamera().GetPosition();

    m_Interface = CreateScope<UserInterface>();

    m_ShadowMap = CreateRef<ShadowMap>();
    if(!m_ShadowMap->Init(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT))
        CORE_ERROR("Shadow map not init.");
    m_OmniShadowMap = CreateRef<OmniShadowMap>();
    if(!m_OmniShadowMap->Init(SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT))
        CORE_ERROR("Omni Shadow map not init.");
    glfwGetFramebufferSize((GLFWwindow*)m_Window->GetWindow(), &framebuffer_width, &framebuffer_height);
}

void LightTestRoom::Init()
{
    this->ObjectInit();
    this->RoomInit();
    this->ModelInit();
    this->ShaderInit();
    this->TextureInit();
    this->LightInit();
}

void LightTestRoom::ObjectInit()
{
    using namespace CustomSpace;
    m_Box = ShapeFactory::Get().ShapeCreator<Box>();
    m_Box->SetPosition(glm::vec3(1.5f, 1.f, 0.f));
    m_Box->SetScale(glm::vec3(.5f, .5f, .5f));
    // m_Box->SetScale(glm::vec3(2.5f));
    glm::mat4 _MM = m_Box->GetTransform()->GetTranslate() * m_Box->GetTransform()->GetRotate() * m_Box->GetTransform()->GetScale();
    m_Box->SetModelMatrix(_MM);
    m_MeshContainer.push_back(m_Box);

    m_Pyramid = ShapeFactory::Get().ShapeCreator<Pyramid>();
    m_Pyramid->SetPosition(glm::vec3(-1.8f, 0.f, -2.f));
    m_Pyramid->SetRotation(45.f, glm::vec3(0.f, 1.f, 0.f));
    // m_Pyramid->SetScale(glm::vec3(2.f, 2.f, 2.f));
    _MM = m_Pyramid->GetTransform()->GetTranslate() * m_Pyramid->GetTransform()->GetRotate() * m_Pyramid->GetTransform()->GetScale();
    m_Pyramid->SetModelMatrix(_MM);
    m_MeshContainer.push_back(m_Pyramid);
}

void LightTestRoom::ModelInit()
{
    m_HeadCrab = CustomSpace::CreateRef<CustomSpace::Model>("../src/Model/headcrab.obj");

    m_Crowbar = CustomSpace::CreateRef<CustomSpace::Model>("../src/Model/crowbar.obj");

    m_PortalGun = CustomSpace::CreateRef<CustomSpace::Model>("../src/Model/portalgun.obj");
}

void LightTestRoom::ShaderInit()
{
    m_ShaderPool = CustomSpace::CreateScope<ShaderPool>();

    m_ShaderPool->getShader(0, "../src/shader/3DModel.vert", "../src/shader/3DModel.frag");
    m_ShaderPool->getShader(1, "../src/shader/LightMaterial.vert", "../src/shader/LightMaterial.frag");
    m_ShaderPool->getShader(2, "../src/shader/2DGameCircle.vert", "../src/shader/2DGameCircle.frag");
    m_ShaderPool->getShader(3, "../src/shader/2DGameTexture.vert", "../src/shader/2DGameTexture.frag");
    m_ShaderPool->getShader(4, "../src/shader/Light.vert", "../src/shader/Light.frag");
    m_ShaderPool->getShader(5, "../src/shader/LightGouraudMaterial.vert", "../src/shader/LightGouraudMaterial.frag");
    m_ShaderPool->getShader(6, "../src/shader/ShadowMap.vert", "../src/shader/ShadowMap.frag");
    m_ShaderPool->getShader(7, "../src/shader/shadowMap_debug.vert", "../src/shader/shadowMap_debug.frag");
    m_ShaderPool->getShader(8, "../src/shader/OmniShadowMap.vert", "../src/shader/OmniShadowMap.frag", "../src/shader/OmniShadowMap.geom");
    m_ShaderPool->getShader(9, "../src/shader/Skybox.vert", "../src/shader/Skybox.frag");
    m_ShaderPool->getShader(1)->SetInt("uMaterial.diffuse", 0);
    m_ShaderPool->getShader(1)->SetInt("uMaterial.specular", 1);
    m_ShaderPool->getShader(1)->SetFloat("uMaterial.shininess", 32.f);
}

void LightTestRoom::TextureInit()
{
    using namespace CustomSpace;
    m_hl2_ceiling = Texture2D::Create("../src/TextureSrc/concreteceiling001a.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_hl2_wall[0] = Texture2D::Create("../src/TextureSrc/building_template015b_a5.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_hl2_wall[1] = Texture2D::Create("../src/TextureSrc/building_template015f.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_hl2_wall_normal[0] = Texture2D::Create("../src/TextureSrc/building_template015b_a1_normal.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_hl2_wall_normal[1] = Texture2D::Create("../src/TextureSrc/building_template015f_normal.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_hl2_wall_middle = Texture2D::Create("../src/TextureSrc/building_template015a.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_hl2_wall_middle_normal = Texture2D::Create("../src/TextureSrc/building_template015a_normal.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_hl2_wood_door = Texture2D::Create("../src/TextureSrc/wooddoor014a.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_hl2_wood_door_normal = Texture2D::Create("../src/TextureSrc/wooddoor014a_normal.tga", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_StoneTex = Texture2D::Create("../src/TextureSrc/stone_wall.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_StoneSpec = Texture2D::Create("../src/TextureSrc/stone_wall_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_WoodTex = Texture2D::Create("../src/TextureSrc/wood.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_WoodSpec = Texture2D::Create("../src/TextureSrc/wood_specular.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_FriendCubeTex = Texture2D::Create("../src/TextureSrc/metal_box_lowres_skin001_na.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_FriendCubeSpec = Texture2D::Create("../src/TextureSrc/metal_box_lowres_skin001_a.tga", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_pt2_tile = Texture2D::Create("../src/TextureSrc/black_floor_metal_001na.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_pt2_tile_spec = Texture2D::Create("../src/TextureSrc/black_floor_metal_001a-RGB.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_pt2_floor_normal = Texture2D::Create("../src/TextureSrc/black_floor_metal_001a_normal.tga", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_hl2_tile = Texture2D::Create("../src/TextureSrc/tilefloor009b.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_hl2_tile_spec = Texture2D::Create("../src/TextureSrc/tilefloor009b_spec_2.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_hl2_floor_normal = Texture2D::Create("../src/TextureSrc/tilefloor009b_normal.tga", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_pt2_wall[0] = Texture2D::Create("../src/TextureSrc/white_wall_tile003b.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_pt2_wall_spec = Texture2D::Create("../src/TextureSrc/white_wall_tile003b_spec.tga", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);
    m_pt2_wall_normal = Texture2D::Create("../src/TextureSrc/white_wall_tile003b_normal.tga", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    m_pt2_ceiling = Texture2D::Create("../src/TextureSrc/white_ceiling_tile002a.tga", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    m_pt2_ceiling_normal = Texture2D::Create("../src/TextureSrc/white_ceiling_tile002a_normal.tga", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
}

void LightTestRoom::LightInit()
{
    using namespace CustomSpace;
    glm::mat4 _MM = glm::mat4(1.f);
    m_DirLight = CreateRef<DirectionLight>();
    m_DirLight->SetAmbient(glm::vec3(.0f, .0f, .0f));
    // m_DirLight->SetAmbient(glm::vec3(.94f, .92f, .78f));
    m_DirLight->SetSpecular(glm::vec3(.1f, .1f, .1f));
    m_DirLight->SetDirection(glm::vec3(-2.f, 4.f, -1.f));
    m_DirLight->SetPosition(glm::vec3(-1.f, 2.f, -2.f));
    _MM = m_DirLight->GetTransform()->GetTranslate();
    m_DirLight->SetModelMatrix(_MM);

    m_PointLight = CreateRef<PointLight>();
    auto _point = std::static_pointer_cast<PointLight>(m_PointLight);
    m_PointLight->SetAmbient(glm::vec3(.94f, .92f, .78f));
    // m_PointLight->SetAmbient(glm::vec3(.001f, .001f, .001f));
    m_PointLight->SetDiffuse(glm::vec3(.1f, .1f, .1f));
    m_PointLight->SetSpecular(glm::vec3(.5f, .5f, .5f));
    m_PointLight->SetPosition(glm::vec3(glm::cos(m_AllTime), 1.5f, glm::sin(m_AllTime)));
    _MM = m_PointLight->GetTransform()->GetTranslate();
    m_PointLight->SetModelMatrix(_MM);
    m_OriginAmbient[0] = m_PointLight->GetLightData()->ambient;
    m_PointLightPos = m_PointLight->GetTransform()->GetLocalPosition();

    m_SpotLight[0] = CreateRef<SpotLight>();
    m_SpotLight[0]->SetAmbient(glm::vec3(.0f, .5f, .0f));
    m_SpotLight[0]->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight[0]->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight[0]->SetPosition(glm::vec3(-1.f, 1.f, -1.f));
    m_SpotLight[0]->SetDirection(glm::vec3(-1.f, -1.f, -1.f));

    m_SpotLight[1] = CreateRef<SpotLight>();
    m_SpotLight[1]->SetAmbient(glm::vec3(.5f, 0.f, .0f));
    m_SpotLight[1]->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight[1]->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight[1]->SetPosition(glm::vec3(0.f, 1.f, 1.f));
    m_SpotLight[1]->SetDirection(glm::vec3(0.f, -1.f, 1.f));

    m_SpotLight[2] = CreateRef<SpotLight>();
    m_SpotLight[2]->SetAmbient(glm::vec3(.0f, 0.f, .5f));
    m_SpotLight[2]->SetDiffuse(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight[2]->SetSpecular(glm::vec3(1.f, 1.f, 1.f));
    m_SpotLight[2]->SetPosition(glm::vec3(1.f, 1.f, -1.f));
    m_SpotLight[2]->SetDirection(glm::vec3(1.f, -1.f, -1.f));
    for(int i = 0; i < 3; i++)
    {
        auto _spot = std::static_pointer_cast<SpotLight>(m_SpotLight[i]);
        _spot->SetInnerCutOff(15.f);
        _spot->SetOuterCutOff(30.5f);
        _MM = m_SpotLight[i]->GetTransform()->GetTranslate();
        m_SpotLight[i]->SetModelMatrix(_MM);
        m_OriginAmbient[i + 1] = m_SpotLight[i]->GetLightData()->ambient;
    }
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

        m_Timer->CalculateTimer();

        CustomSpace::RenderCommand::SetClearColor(glm::vec4(.1f, .1f, .1f, 1.f));
        CustomSpace::RenderCommand::Clear();
        // Shadow map update
        // this->ShadowMapUpdate();
        this->OmniShadowMapUpdate();

        // // Normal scene update
        CustomSpace::RenderCommand::SetViewport(0, 0, framebuffer_width, framebuffer_height);
        CustomSpace::RenderCommand::Clear();

        // Shadow map debug render
        // m_ShaderPool->getShader(7)->Activate();
        // m_ShadowMap->BindForReading(GL_TEXTURE0);
        // m_ShaderPool->getShader(7)->SetInt("depthMap", 0);
        // m_ShaderPool->getShader(7)->SetFloat("near_plane", .1f);
        // m_ShaderPool->getShader(7)->SetFloat("far_plane", 50.f);
        // RenderQuad();

        m_Interface->OnUpdate(*m_Timer);

        CustomSpace::PerspectiveCamera* m_PersCamera = &m_PersController->GetCamera();
        CustomSpace::Renderer::BeginScene(m_PersController->GetCamera());
        CustomSpace::Renderer::BeginScene(*m_OrthoCamera);
        glm::mat4 model = glm::mat4(1.f);

        glDepthFunc(GL_LEQUAL);
        m_ShaderPool->getShader(9)->Activate();
        glm::mat4 view = glm::mat4(glm::mat3(m_PersController->GetCamera().GetViewMatrix())); 
        m_ShaderPool->getShader(9)->SetMat4("projection", m_PersController->GetCamera().GetProjectionMatrix());
        m_ShaderPool->getShader(9)->SetMat4("view", view);
        m_ShaderPool->getShader(9)->SetInt("skybox", 0);
        m_Skybox->Draw();
        glDepthFunc(GL_LESS);

        CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
        _shader->Activate();
        _shader->SetMat4("ulightProjection", m_LightProjection);
        // _shader->SetInt("uShadowMap", 4);
        // m_ShadowMap->BindForReading(GL_TEXTURE0 + 4);
        _shader->SetInt("depthMap", 5);
        m_OmniShadowMap->BindToRead(GL_TEXTURE5);

        // Bind shadow map

        _shader->SetInt("HaveTex", true);
        _shader->SetFloat("far_plane", 25.f);
        _shader->SetFloat3("uViewPos", m_PersController->GetCamera().GetPosition());
        this->LightControl();

        this->RoomUpdate();

        this->RenderNormalScene();


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

        // if(m_CamPosition.x >= 2.f)
        //     m_CamPosition.x = 2.f;
        // else if(m_CamPosition.x <= -2.f)
        //     m_CamPosition.x = -2.f;
        // if(m_CamPosition.z >= 2.f)
        //     m_CamPosition.z = 2.f;
        // else if(m_CamPosition.z <= -2.f)
        //     m_CamPosition.z = -2.f;
        // if(m_CamPosition.y >= 4.5f)
        //     m_CamPosition.y = 4.5f;
        // else if(m_CamPosition.y <= .5f)
        //     m_CamPosition.y = .5f;
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

    if(event.GetKeyCode() == GLFW_KEY_R)
    {
        this->RGBControl(glm::vec3(.01, 0.f, 0.f));
    }

    if(event.GetKeyCode() == GLFW_KEY_G)
    {
        this->RGBControl(glm::vec3(0.f, .01f, 0.f));
    }

    if(event.GetKeyCode() == GLFW_KEY_B)
    {
        this->RGBControl(glm::vec3(0.f, 0.f, .01f));
    }

    if(event.GetKeyCode() == GLFW_KEY_P)
    {
        this->RoomReset();
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

void LightTestRoom::RenderNormalScene()
{
    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
    glm::mat4 model = glm::mat4(1.f);
    m_StoneTex->Bind();
    m_StoneSpec->Bind();
    _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Pyramid->GetTransform()->GetModelMatrix())));
    CustomSpace::Renderer::Submit(_shader, m_Pyramid);
    m_StoneTex->UnBind();
    m_StoneSpec->UnBind();

    m_FriendCubeTex->Bind();
    m_FriendCubeSpec->Bind();
    _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Box->GetTransform()->GetModelMatrix())));
    CustomSpace::Renderer::Submit(_shader, m_Box);
    m_FriendCubeSpec->UnBind();
    m_FriendCubeTex->UnBind();

    m_ShaderPool->getShader(4)->Activate();
    m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(m_DirLight->GetLightData()->ambient, 1.0f));
    CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_DirLight->GetBody());

    m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(m_PointLight->GetLightData()->ambient, 1.0f));
    if(m_Interface->IsButtonActive()[0])
    {
        m_AllTime += m_Timer->GetTick();
        m_PointLight->SetPosition(glm::vec3(glm::cos(m_AllTime), m_PointLight->GetTransform()->GetLocalPosition().y, glm::sin(m_AllTime)));
    }
    model = m_PointLight->GetTransform()->GetTranslate() * m_PointLight->GetTransform()->GetRotate() * m_PointLight->GetTransform()->GetScale();
    m_PointLight->SetModelMatrix(model);
    CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_PointLight->GetBody());

    for(int i = 0; i < 3; i++)
    {
        m_ShaderPool->getShader(4)->SetFloat4("lightColor", glm::vec4(m_SpotLight[i]->GetLightData()->ambient, 1.0f));
        CustomSpace::Renderer::Submit(m_ShaderPool->getShader(4), m_SpotLight[i]->GetBody());
    }

    model = glm::mat4(1.f);
    m_ShaderPool->getShader(1)->Activate();
    m_ShaderPool->getShader(1)->SetMat4("uVP", m_PersController->GetCamera().GetVPMatrix());
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    m_ShaderPool->getShader(1)->SetMat4("uMV", model);
    m_ShaderPool->getShader(1)->SetInt("HaveTex", true);
    m_ShaderPool->getShader(1)->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(model)));
    m_HeadCrab->DrawWithNormalMap(*m_ShaderPool->getShader(1), true);

    model = glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 2.f));
    m_ShaderPool->getShader(1)->SetMat4("uMV", model);
    m_ShaderPool->getShader(1)->SetInt("HaveTex", true);
    m_ShaderPool->getShader(1)->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(model)));
    m_Crowbar->DrawWithNormalMap(*m_ShaderPool->getShader(1), false);

    model = glm::translate(glm::mat4(1.f), glm::vec3(2.f, .15f, -2.f));
    model = glm::rotate(model, glm::radians(-10.f), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(-45.f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(.5f, .5f, .5f));
    m_ShaderPool->getShader(1)->SetMat4("uMV", model);
    m_ShaderPool->getShader(1)->SetInt("HaveTex", true);
    m_ShaderPool->getShader(1)->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(model)));
    m_PortalGun->Draw(*m_ShaderPool->getShader(1));
}

void LightTestRoom::RenderShadowScene()
{
    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(8);
    glm::mat4 model = glm::mat4(1.f);
    for(int i = 0 ; i < m_MeshContainer.size(); i++)
    {
        CustomSpace::Renderer::SubmitShadow(_shader, m_MeshContainer[i]);
    }
    model = glm::translate(model, glm::vec3(0.f, 0.f, 0.f));
    model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
    _shader->SetMat4("uMV", model);
    m_HeadCrab->Draw(*_shader);

    model = glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 2.f));
    _shader->SetMat4("uMV", model);
    m_Crowbar->Draw(*_shader);

    model = glm::translate(glm::mat4(1.f), glm::vec3(2.f, .15f, -2.f));
    model = glm::rotate(model, glm::radians(-10.f), glm::vec3(1, 0, 0));
    model = glm::rotate(model, glm::radians(-45.f), glm::vec3(0, 1, 0));
    model = glm::scale(model, glm::vec3(.5f, .5f, .5f));
    _shader->SetMat4("uMV", model);
    m_PortalGun->Draw(*_shader);
}

void LightTestRoom::RoomInit()
{
    using namespace CustomSpace;

    glm::vec3 _scale = glm::vec3(2.5f, 1.f, 2.5f);
    glm::mat4 _MM(1.f);

    for(int i = 0; i < FLOORNUM; i++)
    {
        m_Ground[i] = ShapeFactory::Get().ShapeCreator<Plane>();
        if(i < 3)
        {
            float _x = 2.5f; float _y = -.0001f; float _z = i * -5.f;
            m_Ground[i]->SetPosition(glm::vec3(_x, _y, _z));

        }
        else
        {
            float _x = -2.5f; float _y = -.0001f; float _z = (i - 3) * -5.f;
            m_Ground[i]->SetPosition(glm::vec3(_x, _y, _z));
        }
        m_Ground[i]->SetScale(_scale);
        m_Ground[i]->SetRotation(180.f);
        _MM = m_Ground[i]->GetTransform()->GetTranslate() * m_Ground[i]->GetTransform()->GetRotate() * m_Ground[i]->GetTransform()->GetScale();
        m_Ground[i]->SetModelMatrix(_MM);
        // m_MeshContainer.push_back(m_Ground[i]);
    }

    for(int i = 0; i < CEILINGNUM; i++)
    {
        m_Ceiling[i] = ShapeFactory::Get().ShapeCreator<Plane>();
        if(i < 3)
        {
            float _z = i * -5.f;
            m_Ceiling[i]->SetPosition(glm::vec3(2.5f, 5.0001f, _z));
        }
        else
        {
            float _z = (i - 3) * -5.f;
            m_Ceiling[i]->SetPosition(glm::vec3(-2.5f, 5.0001f, _z));
        }
        m_Ceiling[i]->SetScale(_scale);

        
        _MM = m_Ceiling[i]->GetTransform()->GetTranslate() * m_Ceiling[i]->GetTransform()->GetRotate() * m_Ceiling[i]->GetTransform()->GetScale();
        m_Ceiling[i]->SetModelMatrix(_MM);
    }
// Half life 2
    m_Wall[0] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[0]->SetPosition(glm::vec3(5.f, 2.5f, 0.f));
    m_Wall[0]->SetScale(_scale);
    m_Wall[0]->SetRotation(-90.f);

    m_Wall[1] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[1]->SetPosition(glm::vec3(5.f, 2.5f, -10.f));
    m_Wall[1]->SetScale(_scale);
    m_Wall[1]->SetRotation(-90.f);

    m_Wall[2] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[2]->SetPosition(glm::vec3(2.5f, 2.5f, 2.5f));
    m_Wall[2]->SetScale(_scale);
    m_Wall[2]->SetRotation(90.f, glm::vec3(1.f, 0, 0));

    m_Wall[3] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[3]->SetPosition(glm::vec3(2.5f, 2.5f, -12.5f));
    m_Wall[3]->SetScale(_scale);
    m_Wall[3]->SetRotation(-90.f, glm::vec3(1, 0, 0));

    m_Wall[4] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[4]->SetPosition(glm::vec3(5.f, 2.5f, -5.f));
    m_Wall[4]->SetScale(_scale);
    m_Wall[4]->SetRotation(-90.f);

// Portal 2
    m_Wall[5] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[5]->SetPosition(glm::vec3(-5.f, 2.5f, 0.f));
    m_Wall[5]->SetScale(_scale);
    m_Wall[5]->SetRotation(90.f);

    m_Wall[6] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[6]->SetPosition(glm::vec3(-5.f, 2.5f, -10.f));
    m_Wall[6]->SetScale(_scale);
    m_Wall[6]->SetRotation(90.f);

    m_Wall[7] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[7]->SetPosition(glm::vec3(-2.5f, 2.5f, 2.5f));
    m_Wall[7]->SetScale(_scale);
    m_Wall[7]->SetRotation(90.f, glm::vec3(1.f, 0, 0));

    m_Wall[8] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[8]->SetPosition(glm::vec3(-2.5f, 2.5f, -12.5f));
    m_Wall[8]->SetScale(_scale);
    m_Wall[8]->SetRotation(-90.f, glm::vec3(1, 0, 0));

    m_Wall[9] = ShapeFactory::Get().ShapeCreator<Plane>();
    m_Wall[9]->SetPosition(glm::vec3(-5.f, 2.5f, -5.f));
    m_Wall[9]->SetScale(_scale);
    m_Wall[9]->SetRotation(90.f);
    for(int i = 0; i < 10; i++)
    {
        if(i == 2 || i == 7)
            _MM = m_Wall[i]->GetTransform()->GetTranslate() * m_Wall[i]->GetTransform()->GetRotate() * m_Wall[i]->GetTransform()->GetScale();
        else if(i == 3 || i == 8)
            _MM = m_Wall[i]->GetTransform()->GetTranslate() * glm::rotate(glm::mat4(1.f), glm::radians(180.f), glm::vec3(0, 0, 1)) * m_Wall[i]->GetTransform()->GetRotate() * m_Wall[i]->GetTransform()->GetScale();
        else
            _MM = m_Wall[i]->GetTransform()->GetTranslate() * glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(1.f, 0, 0)) * m_Wall[i]->GetTransform()->GetRotate() * m_Wall[i]->GetTransform()->GetScale();
        m_Wall[i]->SetModelMatrix(_MM);
        // m_MeshContainer.push_back(m_Wall[i]);
    }

// Inner wall
    _scale = glm::vec3(1.f, 1.f, 2.5f);
    glm::vec3 _axis = glm::vec3(1.f, 0.f, 0.f);
    float _radians = 90.f;
    for(int i = 0; i < 4; i++)
    {
        m_InnerWall[i] = ShapeFactory::Get().ShapeCreator<Plane>();
        if(i < 2)
        {
            m_InnerWall[i]->SetPosition(glm::vec3(1 + (i * 3), 2.5f, -2.5));
        }
        else
        {
            m_InnerWall[i]->SetPosition(glm::vec3(1 + ((i - 2) * 3), 2.5f, -7.5));
        }
        m_InnerWall[i]->SetScale(_scale);
        m_InnerWall[i]->SetRotation(_radians, _axis);
        _MM =  m_InnerWall[i]->GetTransform()->GetTranslate() * m_InnerWall[i]->GetTransform()->GetRotate() * m_InnerWall[i]->GetTransform()->GetScale();
        m_InnerWall[i]->SetModelMatrix(_MM);
        m_MeshContainer.push_back(m_InnerWall[i]);
    }

    _scale = glm::vec3(.5f, 1.f, 1.25f);
    for(int i = 0; i < 2; i++)
    {
        m_Middle_Wall[i] = ShapeFactory::Get().ShapeCreator<Plane>();
        m_Middle_Wall[i]->SetPosition(glm::vec3(2.5f, 3.75f, -2.5 + (i * -5.f)));
        m_Middle_Wall[i]->SetScale(_scale);
        m_Middle_Wall[i]->SetRotation(_radians, _axis);
        _MM = m_Middle_Wall[i]->GetTransform()->GetTranslate() * m_Middle_Wall[i]->GetTransform()->GetRotate() * m_Middle_Wall[i]->GetTransform()->GetScale();
        m_Middle_Wall[i]->SetModelMatrix(_MM);
        m_MeshContainer.push_back(m_Middle_Wall[i]);

        m_WoodDoor[i] = ShapeFactory::Get().ShapeCreator<Plane>();
        m_WoodDoor[i]->SetPosition(glm::vec3(2.5f, 1.25f, -2.5  + (i * -5.f)));
        m_WoodDoor[i]->SetScale(_scale);
        m_WoodDoor[i]->SetRotation(_radians, _axis);
        _MM = m_WoodDoor[i]->GetTransform()->GetTranslate() * m_WoodDoor[i]->GetTransform()->GetRotate() * m_WoodDoor[i]->GetTransform()->GetScale();
        m_WoodDoor[i]->SetModelMatrix(_MM);
        m_MeshContainer.push_back(m_WoodDoor[i]);
    }

}

void LightTestRoom::ShadowMapUpdate()
{
    // Direct shadow map
    // GLfloat aspect = (GLfloat)SHADOW_MAP_WIDTH / SHADOW_MAP_HEIGHT;
    // glm::mat4 PerspectiveProjection = glm::perspective(glm::radians(120.f), aspect, .1f, 50.f);
    // glm::mat4 lightView = glm::lookAt(m_SpotLight[0]->GetTransform()->GetLocalPosition(), m_SpotLight[0]->GetLightData()->direction, glm::vec3(0.f, 1.f, 0.f));
    // m_LightProjection = PerspectiveProjection * lightView;
    glm::mat4 orthoProjection = glm::ortho(-10.f, 10.f, -10.f, 10.f, .1f, 7.5f);
    glm::mat4 lightView = glm::lookAt(m_DirLight->GetTransform()->GetLocalPosition(), glm::vec3(0.f), glm::vec3(0.f, 1.f, 0.f));
    m_LightProjection = orthoProjection * lightView;

    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(6);
    m_ShadowMap->BindForUpdate();
    glClear(GL_DEPTH_BUFFER_BIT);

    _shader->Activate();
    _shader->SetMat4("uLightProjection", m_LightProjection);

    glCullFace(GL_FRONT);
    this->RenderShadowScene();
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void LightTestRoom::OmniShadowMapUpdate()
{
    //Omni shadow map
    glm::mat4 model = glm::mat4(1.f);
    float aspect = (float)SHADOW_MAP_WIDTH / (float)SHADOW_MAP_HEIGHT;
    float near = .1f, far = 25.f;
    glm::mat4 shadowProj = glm::perspective(glm::radians(90.f), aspect, near, far);

    std::vector<glm::mat4> shadowTransform;
    glm::vec3 _point_pos = m_PointLight->GetTransform()->GetLocalPosition();
    shadowTransform.push_back(shadowProj * glm::lookAt(_point_pos, _point_pos + glm::vec3(1.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f)));
    shadowTransform.push_back(shadowProj * glm::lookAt(_point_pos, _point_pos + glm::vec3(-1.f, 0.f, 0.f), glm::vec3(0.f, -1.f, 0.f)));
    shadowTransform.push_back(shadowProj * glm::lookAt(_point_pos, _point_pos + glm::vec3(0.f, 1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)));
    shadowTransform.push_back(shadowProj * glm::lookAt(_point_pos, _point_pos + glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 0.f, -1.f)));
    shadowTransform.push_back(shadowProj * glm::lookAt(_point_pos, _point_pos + glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, -1.f, 0.f)));
    shadowTransform.push_back(shadowProj * glm::lookAt(_point_pos, _point_pos + glm::vec3(0.f, 0.f, -1.f), glm::vec3(0.f, -1.f, 0.f)));

    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(8);

    m_OmniShadowMap->BindToWrite();

    glClear(GL_DEPTH_BUFFER_BIT);
    
    _shader->Activate();

    for(unsigned int i = 0; i < 6; i++)
        _shader->SetMat4(("shadowMatrices[" + std::to_string(i) + "]").c_str(), shadowTransform[i]);
    _shader->SetFloat("far_plane", far);
    _shader->SetFloat3("lightPos", _point_pos);
    glCullFace(GL_FRONT);
    this->RenderShadowScene();
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

void LightTestRoom::RoomUpdate()
{
    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
    _shader->SetInt("uMaterial.normalmap", 2);
    _shader->SetInt("HaveNormal", true);
    for(int i = 0; i < FLOORNUM; i++)
    {
        if(i < 3)
        {
            m_hl2_tile->Bind();
            m_hl2_tile_spec->Bind();
            m_hl2_floor_normal->Bind();
            _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Ground[i]->GetTransform()->GetModelMatrix())));
            CustomSpace::Renderer::Submit(_shader, m_Ground[i]);
            m_hl2_tile->UnBind();
            m_hl2_tile_spec->UnBind();
            m_hl2_floor_normal->UnBind();
        }
        else
        {
            m_pt2_tile->Bind();
            m_pt2_tile_spec->Bind();
            m_pt2_floor_normal->Bind();
            _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Ground[i]->GetTransform()->GetModelMatrix())));
            CustomSpace::Renderer::Submit(_shader, m_Ground[i]);
            m_pt2_tile->UnBind();
            m_pt2_tile_spec->UnBind();
            m_pt2_floor_normal->UnBind();
        }
    }

    m_hl2_wall[1]->Bind();
    m_hl2_wall_normal[1]->Bind();
    for(int i = 0; i < 4; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Wall[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_Wall[i]);
    }

    //  Inner update
    glDisable(GL_CULL_FACE);
    for(int i = 0; i < 4; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_InnerWall[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_InnerWall[i]);
    }

    m_hl2_wall_middle->Bind();
    m_hl2_wall_middle_normal->Bind();
    for(int i = 0; i < 2; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Middle_Wall[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_Middle_Wall[i]);
    }
    m_hl2_wall_middle->UnBind();
    m_hl2_wall_middle_normal->UnBind();

    m_hl2_wood_door->Bind();
    m_hl2_wood_door_normal->Bind();
    for(int i = 0; i < 2; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_WoodDoor[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_WoodDoor[i]);
    }
    m_hl2_wood_door->UnBind();
    m_hl2_wood_door_normal->UnBind();

    glEnable(GL_CULL_FACE); // Double faces

    m_hl2_wall_normal[1]->UnBind();
    m_hl2_wall[1]->UnBind();

    m_hl2_wall[0]->Bind();
    m_hl2_wall_normal[0]->Bind();
    _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Wall[4]->GetTransform()->GetModelMatrix())));
    CustomSpace::Renderer::Submit(_shader, m_Wall[4]);
    m_hl2_wall[0]->UnBind();
    m_hl2_wall_normal[0]->UnBind();


    _shader->SetInt("HaveNormal", false); // Normal section

    m_hl2_ceiling->Bind();
    for(int i = 0; i < 3; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Ceiling[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_Ceiling[i]);
    }
    m_hl2_ceiling->UnBind();



    _shader->SetInt("HaveNormal", true);
    m_pt2_wall[0]->Bind();
    m_pt2_wall_spec->Bind();
    m_pt2_wall_normal->Bind();
    for(int i = 5; i < 10; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Wall[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_Wall[i]);
    }
    m_pt2_wall[0]->UnBind();
    m_pt2_wall_spec->UnBind();
    m_pt2_wall_normal->UnBind();
    
    m_pt2_ceiling->Bind();
    m_pt2_ceiling_normal->Bind();
    for(int i = 3; i < CEILINGNUM; i++)
    {
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Ceiling[i]->GetTransform()->GetModelMatrix())));
        CustomSpace::Renderer::Submit(_shader, m_Ceiling[i]);
    }
    m_pt2_ceiling->UnBind();
    m_pt2_ceiling_normal->UnBind();
    _shader->SetInt("HaveNormal", false);
}

void LightTestRoom::LightControl()
{
    CustomSpace::Ref<Shader> _shader = m_ShaderPool->getShader(1);
    _shader->Activate();
    _shader->SetInt("HaveDirLight", true);
    _shader->SetFloat3("uDirLight.position", m_DirLight->GetTransform()->GetLocalPosition());
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
    _shader->SetInt("uSpotLightNum", 3);
    for(int i = 0; i < 3; i++)
    {
        if(!m_Interface->IsButtonActive()[i + 1])
        {
            std::string s_i = std::to_string(i);
            _shader->SetFloat3(("uSpotLight[" + s_i + "].position").c_str(), m_SpotLight[i]->GetTransform()->GetLocalPosition());
            _shader->SetFloat3(("uSpotLight[" + s_i + "].direction").c_str(), m_SpotLight[i]->GetLightData()->direction);
            _shader->SetFloat3(("uSpotLight[" + s_i + "].ambient").c_str(), m_SpotLight[i]->GetLightData()->ambient);
            _shader->SetFloat3(("uSpotLight[" + s_i + "].diffuse").c_str(), m_SpotLight[i]->GetLightData()->diffuse);
            _shader->SetFloat3(("uSpotLight[" + s_i + "].specular").c_str(), m_SpotLight[i]->GetLightData()->specular);
            auto _spot = std::static_pointer_cast<CustomSpace::SpotLight>(m_SpotLight[i]);
            _shader->SetFloat(("uSpotLight[" + s_i + "].constant").c_str(), 1.f);
            _shader->SetFloat(("uSpotLight[" + s_i + "].linear").c_str(), _spot->GetLinear());
            _shader->SetFloat(("uSpotLight[" + s_i + "].quadratic").c_str(), _spot->GetQuadratic());
            _shader->SetFloat(("uSpotLight[" + s_i + "].innerCutOff").c_str(), _spot->GetInner());
            _shader->SetFloat(("uSpotLight[" + s_i + "].outerCutOff").c_str(), _spot->GetOuter());
        }
        else
        {
            std::string s_i = std::to_string(i);
            _shader->SetFloat3(("uSpotLight[" + s_i + "].position").c_str(), glm::vec3(0.f));
            _shader->SetFloat3(("uSpotLight[" + s_i + "].direction").c_str(), glm::vec3(0.f));
            _shader->SetFloat3(("uSpotLight[" + s_i + "].ambient").c_str(), glm::vec3(0.f));
            _shader->SetFloat3(("uSpotLight[" + s_i + "].diffuse").c_str(), glm::vec3(0.f));
            _shader->SetFloat3(("uSpotLight[" + s_i + "].specular").c_str(), glm::vec3(0.f));
            auto _spot = std::static_pointer_cast<CustomSpace::SpotLight>(m_SpotLight[i]);
            _shader->SetFloat(("uSpotLight[" + s_i + "].constant").c_str(), 1.f);
            _shader->SetFloat(("uSpotLight[" + s_i + "].linear").c_str(), 0.f);
            _shader->SetFloat(("uSpotLight[" + s_i + "].quadratic").c_str(), 0.f);
            _shader->SetFloat(("uSpotLight[" + s_i + "].innerCutOff").c_str(), 0.f);
            _shader->SetFloat(("uSpotLight[" + s_i + "].outerCutOff").c_str(), 0.f);
        }
    }
}

void LightTestRoom::RGBControl(const glm::vec3& value)
{
    switch (m_Interface->LastChooseButton())
    {
    case 0:
        {
            float r_v = m_PointLight->GetLightData()->ambient.r + value.r;
            float g_v = m_PointLight->GetLightData()->ambient.g + value.g;
            float b_v = m_PointLight->GetLightData()->ambient.b + value.b;
            if(r_v > 1.f) r_v = 0.f; if(g_v > 1.f) g_v = 0; if(b_v > 1.f) b_v = 0; 
            m_PointLight->SetAmbient(glm::vec3(r_v, g_v, b_v));
        } 
        break;
    case 1:
        {
            float r_v = m_SpotLight[0]->GetLightData()->ambient.r + value.r;
            float g_v = m_SpotLight[0]->GetLightData()->ambient.g + value.g;
            float b_v = m_SpotLight[0]->GetLightData()->ambient.b + value.b;
            if(r_v > 1.f) r_v = 0.f; if(g_v > 1.f) g_v = 0; if(b_v > 1.f) b_v = 0; 
            m_SpotLight[0]->SetAmbient(glm::vec3(r_v, g_v, b_v));
        }    
        break;
    case 2:
        {
            float r_v = m_SpotLight[1]->GetLightData()->ambient.r + value.r;
            float g_v = m_SpotLight[1]->GetLightData()->ambient.g + value.g;
            float b_v = m_SpotLight[1]->GetLightData()->ambient.b + value.b;
            if(r_v > 1.f) r_v = 0.f; if(g_v > 1.f) g_v = 0; if(b_v > 1.f) b_v = 0; 
            m_SpotLight[1]->SetAmbient(glm::vec3(r_v, g_v, b_v));
        }
        break;
    case 3:
        {
            float r_v = m_SpotLight[2]->GetLightData()->ambient.r + value.r;
            float g_v = m_SpotLight[2]->GetLightData()->ambient.g + value.g;
            float b_v = m_SpotLight[2]->GetLightData()->ambient.b + value.b;
            if(r_v > 1.f) r_v = 0.f; if(g_v > 1.f) g_v = 0; if(b_v > 1.f) b_v = 0; 
            m_SpotLight[2]->SetAmbient(glm::vec3(r_v, g_v, b_v));
        }
        break;
    default:
        break;
    }
}

void LightTestRoom::RoomReset()
{
    m_Interface->Reset();
    m_AllTime = 0;
    m_PointLight->SetPosition(m_PointLightPos);
    m_PointLight->SetAmbient(m_OriginAmbient[0]);

    for(int i = 0; i < SPOTLIGHTNUM; i++)
    {
        m_SpotLight[i]->SetAmbient(m_OriginAmbient[i + 1]);
    }
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void LightTestRoom::RenderQuad()
{
    if (quadVAO == 0)
        {
            float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &quadVAO);
            glGenBuffers(1, &quadVBO);
            glBindVertexArray(quadVAO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        }
        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        glBindVertexArray(0);
}
