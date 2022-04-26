#include"../include/Scene.h"

namespace CustomSpace
{
    Scene::Scene()
    {
        this->Init();
    }

    Scene::~Scene()
    {

    }

    void Scene::Init()
    {
        m_OriginTransform[0] = glm::vec3(0, -9.6, -1);
        m_OriginTransform[1] = glm::vec3(0, 0, -1);
        m_OriginTransform[2] = glm::vec3(0, 9.6, -1);
        m_Factory = CreateRef<ShapeFactory>();        


        m_Background = m_Factory->ShapeCreator<Quad>();
        m_Background->SetPosition(m_OriginTransform[1]);
        m_Background->SetScale(glm::vec3(4.8, 9.6, 0));
        m_Texture = Texture2D::Create("../src/TextureSrc/T_PurpleBackground_Version1_Layer1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

        m_Background2 = m_Factory->ShapeCreator<Quad>();
        m_Background2->SetPosition(m_OriginTransform[2]);
        m_Background2->SetScale(glm::vec3(4.8, 9.6, 0));
        m_Texture2 = Texture2D::Create("../src/TextureSrc/T_YellowBackground_Version1_Layer1.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);

        m_CollisionTest = m_Factory->ShapeCreator<Quad>();
        m_CollisionTest->SetPosition(glm::vec3(2, 3, 0));
        m_CollisionTest->GetBounding()->SetNeedTest(true);

        m_Player = CreateRef<APlayer>(m_Factory);
        m_Transform = glm::vec3(0, -3.5, 0);
        if(m_Player != nullptr)
        {
            m_Player->SetPosition(m_Transform);
            m_Player->SetScale(glm::vec3(.55, .65, 0));
        }
    }
    void Scene::Update(CoreTimer& time)
    {
        m_FrameTime += time.GetFrameTime();
        m_Texture->Bind();
        CustomSpace::Renderer::Submit(m_Background->GetVertexData()->m_Shader, m_Background);
        m_Background->GetVertexData()->m_Shader->SetInt("tex0", 0);
        m_Texture->UnBind();
        m_Texture2->Bind();
        CustomSpace::Renderer::Submit(m_Background2->GetVertexData()->m_Shader, m_Background2);
        m_Background2->GetVertexData()->m_Shader->SetInt("tex0", 1);
        m_Texture2->UnBind();

        if(m_FrameTime >= time.GetDeltaTick())
        {
            float CurrentPos = m_Background->GetTransform()->m_Position.y;
            CurrentPos -= (time.GetTick() * m_MoveSpeed);

            if(CurrentPos <= -9.6)
            {
                CurrentPos = CurrentPos + 2 * 9.6;
            }
            m_Background->SetPosition(CurrentPos, 2);

            CurrentPos = m_Background2->GetTransform()->m_Position.y;
            CurrentPos -= time.GetTick() * m_MoveSpeed;

            if(CurrentPos <= -9.6)
            {
                CurrentPos = CurrentPos + 2 * 9.6;
            }
            m_Background2->SetPosition(CurrentPos, 2);
            m_FrameTime -= time.GetDeltaTick();
        }

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_A))
            m_Transform.x -= (float)m_PlayerSpeed * time.GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_D))
            m_Transform.x += (float)m_PlayerSpeed * time.GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_W))
            m_Transform.y += (float)m_PlayerSpeed * time.GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_S))
            m_Transform.y -= (float)m_PlayerSpeed * time.GetTick();

        m_Player->SetPosition(m_Transform);
        m_Player->Update(time);
        Renderer::Submit(m_CollisionTest->GetVertexData()->m_Shader, m_CollisionTest);
        if(m_Player->GetBounding()->Intersects(m_CollisionTest->GetBounding()))
        {
            CORE_WARN("Collide : {0}", m_Player->GetBounding()->GetBoundingVolume()->Radius_NS);
        }
    }
}