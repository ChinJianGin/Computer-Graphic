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
        m_OriginTransform[0] = { glm::vec3(0, -9.6, -1) };
        m_OriginTransform[1] = { glm::vec3(0,    0, -1) };
        m_OriginTransform[2] = { glm::vec3(0,  9.6, -1) };
        m_Factory = CreateRef<ShapeFactory>();        

        Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem(m_Factory);
        if(ProSystem == nullptr)
        {
            return;
        }

        CORE_INFO("Projectile num : {0}", ProSystem->GetFreeList()->size());
        
        m_Background = m_Factory->ShapeCreator<Quad>();
        m_Background->SetPosition(m_OriginTransform[1]);
        m_Background->SetScale(glm::vec3(4.8, 9.6, 0));
        m_Texture = Texture2D::Create("../src/TextureSrc/T_PurpleBackground_Version1_Layer1.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);

        m_Background2 = m_Factory->ShapeCreator<Quad>();
        m_Background2->SetPosition(m_OriginTransform[2]);
        m_Background2->SetScale(glm::vec3(4.8, 9.6, 0));
        m_Texture2 = Texture2D::Create("../src/TextureSrc/T_PurpleBackground_Version4_Layer1.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_UNSIGNED_BYTE);

        m_Projectile[0] = Texture2D::Create("../src/TextureSrc/PlayerProjectile.png", GL_TEXTURE_2D, GL_TEXTURE20, GL_UNSIGNED_BYTE);
        m_Projectile[1] = Texture2D::Create("../src/TextureSrc/NormalProjectile.png", GL_TEXTURE_2D, GL_TEXTURE21, GL_UNSIGNED_BYTE);

        m_Player = CreateRef<APlayer>(m_Factory);
        m_Transform = glm::vec3(0, -3.5, -.5);
        if(m_Player != nullptr)
        {
            m_Player->SetPosition(m_Transform);
            m_Player->SetScale(glm::vec3(.45, .55, 0));
        }

        m_Normal = CreateRef<NormalEnemy>(m_Factory);
        if(m_Normal != nullptr)
        {
            m_Normal->SetPosition(glm::vec3(0.f, 3.f, -.4f));
        }

        m_UsedNormalEnemy = CreateScope<SinglyLinkedList<Ref<Enemy>>>();
        for(int i = 0; i < NORMAL_NUM; i++)
        {
            m_Normals[i] = CreateRef<NormalEnemy>(m_Factory);
            m_Normals[i]->SetPosition(glm::vec3(-2.f + (i * 0.25), 5.f, -.4f));
        }

        m_Elite = CreateRef<EliteEnemy>(m_Factory);
        if(m_Elite != nullptr)
        {
            m_Elite->SetPosition(glm::vec3(-2, 3, -.4f));
        }

        m_Boss = CreateRef<BossEnemy>(m_Factory);
        if(m_Boss != nullptr)
        {
            m_Boss->SetPosition(glm::vec3(0, 2, -.4f));
        }
    }
    void Scene::Update(CoreTimer& time)
    {
        /**
         * @brief Background
         * 
         */
#pragma region BACKGROUND_CONTROL
        m_FrameTime += time.GetFrameTime();
        m_RunTime += time.GetTick();
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
#pragma endregion BACKGROUND_CONTROL
        /**
         * @brief Player section
         * 
         */
        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_LEFT))
            m_Transform.x -= (float)m_PlayerSpeed * time.GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_RIGHT))
            m_Transform.x += (float)m_PlayerSpeed * time.GetTick();

        if(CustomSpace::Input::IsKeyDown(GLFW_KEY_UP))
            m_Transform.y += (float)m_PlayerSpeed * time.GetTick();
        else if(CustomSpace::Input::IsKeyDown(GLFW_KEY_DOWN))
            m_Transform.y -= (float)m_PlayerSpeed * time.GetTick();

        m_Player->SetPosition(m_Transform);
        m_Player->Update(time);
       
        /**
        * @brief TimeLine 
        * 
        */
        if(m_RunTime <= 30) // Phase 1
        {
#pragma region OPENING
            m_PhaseTime += time.GetTick();
            uint8_t n = 0;
            glm::vec3 NormalPosition = glm::vec3(0);
            float _x = 0.f;
            float _y = 0.f;
            float _z = m_Normals[0]->GetTransform()->m_Position.z;
            if(m_RunTime <= 2) // Normal enemies in
            {
                for(int i = 0; i < 5; i++)
                {
                    n = i * 4;
                    NormalPosition = m_Normals[n]->GetTransform()->m_Position;
                    _y = NormalPosition.y;
                    _x = NormalPosition.x;
                    if(i % 2 == 1)
                    {
                        if(_y > .75f)
                        {
                            _y -= (float)(.0015f * (sinf(m_RunTime) + 1.f));
                        }
                        else
                        {
                            _y = .75f;
                        }
                    }
                    else
                    {
                        if(_y > 2.25f)
                        {
                            _y -= (float)(.001f * (sinf(m_RunTime) + 1.f));
                        }
                        else
                        {
                            _y = 2.25f;
                        }
                    }
                    m_Normals[n]->SetEnableActor(true);
                    m_Normals[n]->SetPosition(glm::vec3(_x, _y, _z));
                    m_Normals[n]->SetTarget(m_Player);
                    m_Normals[n]->Update(time);
                    if(m_UsedNormalEnemy->size() < 5)
                        m_UsedNormalEnemy->push_back(m_Normals[n]);
                }
            }
            else if(m_UsedNormalEnemy->size() > 0)
            {
                if(m_RunTime <= 25) // Normal enemies stay
                {
                    if(!m_PhaseActive[0])
                    {
                        m_PhaseTime = m_PhaseTime - m_RunTime;
                        m_PhaseActive[0] = true;
                    }
                    uint8_t i = 0;
                    if(m_OriginPosition[0] == glm::vec3(0))
                    {
                        for(auto it = m_UsedNormalEnemy->begin(); it != m_UsedNormalEnemy->end(); ++it)
                        {
                            m_OriginPosition[i] = it.getdata()->GetTransform()->m_Position;
                            i++;
                        }
                        uint8_t i = 0;
                    }
                    for(auto it = m_UsedNormalEnemy->begin(); it != m_UsedNormalEnemy->end(); ++it)
                    {
                        _x = m_OriginPosition[i].x;
                        _y = m_OriginPosition[i].y;
                        float sin_x = sinf(m_PhaseTime);
                        if(i % 2 == 1)
                        {
                            _x += (float)(.6f * sin_x);
                        }
                        else
                        {
                            _x -= (float)(.25f * sin_x);
                        }
                        it.getdata()->SetTarget(m_Player);
                        it.getdata()->SetPosition(glm::vec3(_x, _y, _z));
                        it.getdata()->Update(time);
                        i++;
                    }
                }
                else // Normal enemies out
                {
                    if(m_UsedNormalEnemy->size() > 0)
                    {
                        for(auto it = m_UsedNormalEnemy->begin(); it != m_UsedNormalEnemy->end(); ++it)
                        {
                            _x = it.getdata()->GetTransform()->m_Position.x;
                            _y = it.getdata()->GetTransform()->m_Position.y;
                            _y += 1 * time.GetTick();
                            it.getdata()->SetPosition(glm::vec3(_x, _y, _z));
                            it.getdata()->Update(time);
                                if(_y >= 4.8f)
                                {
                                    it.getdata()->SetEnableActor(false);
                                    m_UsedNormalEnemy->erase(it.get_current_node());
                                } 
                        }
                    } 
                }
            }
#pragma endregion OPENING
            else  // random spawn normal enemy
            {

            }
        }
        else if(m_RunTime <= 70) // Phase 2
        {
            GAME_INFO("Phase two");
            m_Normal->SetEnableActor(false);
            m_Elite->SetEnableActor(true);
            m_Elite->Update(time);
        }
        else // Boss Phase
        {
            GAME_INFO("Boss fight.");
            m_Boss->SetEnableActor(true);
            m_Boss->Update(time);
        }

        Scope<ProjectileSystem>& ProSystem = ProjectileSystem::GetProjectileSystem();
        for(auto it = ProSystem->GetUsedList()->begin(); it != ProSystem->GetUsedList()->end(); ++it)
        {
            if(it != nullptr)
            {
                m_Projectile[0]->Bind();
                m_Projectile[1]->Bind();
                it.getdata()->Update(time);
                m_Projectile[0]->UnBind();
                m_Projectile[1]->UnBind();
                if(it.getdata()->GetTransform()->m_Position.y > 5.f || it.getdata()->GetTransform()->m_Position.y < -5.f)
                {
                    it.getdata()->SetTeamID(Projectile::TeamID::Neutral);
                    ProSystem->GetUsedList()->erase(it.get_current_node());
                    ProSystem->GetFreeList()->push_back(it.getdata());
                }
            }
        }
    }

    void Scene::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT(Scene::OnKeyPressedEvent));

        m_Player->OnEvent(event);
    }

    bool Scene::OnKeyPressedEvent(KeyPressedEvent& event)
    {
        return false;
    }
}