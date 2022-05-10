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
            m_Player->GetBounding()->SetNeedTest(true);
            m_Player->SetScale(glm::vec3(.45, .55, 0));
        }

        m_UsedNormalEnemy = CreateScope<SinglyLinkedList<Ref<Enemy>>>();
        m_FreeNormalEnemy = CreateScope<SinglyLinkedList<Ref<Enemy>>>();
        m_RandSpawnEnemy = CreateScope<SinglyLinkedList<Ref<Enemy>>>();
        for(int i = 0; i < NORMAL_NUM; i++)
        {
            m_Normals[i] = CreateRef<NormalEnemy>(m_Factory);
            m_FreeNormalEnemy->push_back(m_Normals[i]);
        }

        for(int i = 0; i < ELITE_NUM; i++)
        {
            m_Elite[i] = CreateRef<EliteEnemy>(m_Factory);
            m_Elite[i]->SetPosition(glm::vec3((i - 1) * 1.2f, 5.f, -.4f));
            m_EliteOriginPosition[i] = m_Elite[i]->GetTransform()->m_Position;
        }

        m_Boss = CreateRef<BossEnemy>(m_Factory);
        if(m_Boss != nullptr)
        {
            m_Boss->SetPosition(glm::vec3(0, -8.f, -.2f));
            m_Boss->SetScale(glm::vec3(8.f, 8.f, 1.f));
            m_Boss->SetRotation(M_PI);
            m_BossOriginPosition = m_Boss->GetTransform()->m_Position;
        }

        AddSpeed = m_Factory->ShapeCreator<Quad>();
        AddSpeed->SetScale(glm::vec3(.5f, .5f, 1.f));
        AddSpeed->SetPosition(glm::vec3(1, -3.5, -.5));
        AddSpeed->GetBounding()->SetNeedTest(true);
        m_AddSpeedTex = Texture2D::Create("../src/TextureSrc/AddSpeed.png", GL_TEXTURE_2D, GL_TEXTURE22, GL_UNSIGNED_BYTE);
        SpeedCal = CoolDown;
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

        if(AddSpeed->GetBounding()->IsNeedTest())
        {
            m_AddSpeedTex->Bind();
            Renderer::Submit(AddSpeed->GetVertexData()->m_Shader, AddSpeed);
            AddSpeed->GetVertexData()->m_Shader->SetInt("tex0", 22);
            m_AddSpeedTex->UnBind();
            if(AddSpeed->GetBounding()->Intersects(m_Player->GetBounding()))
            {
                AddSpeed->GetBounding()->SetNeedTest(false);
                b_AddSpeed = true;
            }
        }

        if(m_FrameTime >= time.GetDeltaTick())
        {
            float CurrentPos = m_Background->GetTransform()->m_Position.y;
            CurrentPos -= (time.GetTick() * m_MoveSpeed);

            if(CurrentPos <= -9.6)
            {
                CurrentPos = CurrentPos + 2 * 9.6;
            }
            m_Background->SetPosition(CurrentPos, 2);
            AddSpeed->SetPosition(glm::vec3(AddSpeed->GetTransform()->m_Position.x, CurrentPos, AddSpeed->GetTransform()->m_Position.z));

            CurrentPos = m_Background2->GetTransform()->m_Position.y;
            CurrentPos -= time.GetTick() * m_MoveSpeed;

            if(CurrentPos <= -9.6)
            {
                CurrentPos = CurrentPos + 2 * 9.6;
            }
            m_Background2->SetPosition(CurrentPos, 2);
            AddSpeed->SetPosition(glm::vec3(AddSpeed->GetTransform()->m_Position.x, CurrentPos, AddSpeed->GetTransform()->m_Position.z));
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
        m_Player->SetTarget(m_Boss);
        m_Player->Update(time);
       
       if(b_AddSpeed)
       {
           SpeedCal -= time.GetTick();
           m_PlayerSpeed = 3.f;
           if(SpeedCal <= 0)
           {
               m_PlayerSpeed = 1.5f;
               b_AddSpeed = false;
           }
       }
        /**
        * @brief TimeLine 
        * 
        */
       if(!b_GameOver)
       {
        if(m_RunTime <= 20) // Phase 1
        {
#pragma region OPENING
            m_PhaseTime += time.GetTick();
            uint8_t n = 0;
            glm::vec3 NormalPosition = glm::vec3(0);
            float _x = 0.f;
            float _y = 0.f;
            float _z = m_Normals[0]->GetTransform()->m_Position.z;
            Ref<Enemy> get;
            if(m_RunTime <= M_PI_2) // Normal enemies in
            {
                if(!m_PhaseActive[0])
                {
                    for(int i = 0; i < 5; i++)
                    {
                        n = i * 4;
                        get = m_FreeNormalEnemy->front()->get();
                        get->SetPosition(glm::vec3(-2.f + (n * 0.25f), 5.f, -.4f));
                        get->GetBounding()->SetNeedTest(true);
                        m_NormalOriginPosition[i] = get->GetTransform()->m_Position;

                        if(m_UsedNormalEnemy->size() < 5)
                        {
                            m_FreeNormalEnemy->pop_front();
                            m_UsedNormalEnemy->push_back(get);
                        }
                    }
                    m_PhaseTime = 0;
                    m_PhaseActive[0] = true;
                }
                else
                {
                    uint8_t LocalCount = 0;
                    for(auto it = m_UsedNormalEnemy->begin(); it != m_UsedNormalEnemy->end(); ++it)
                    {
                        _y = m_NormalOriginPosition[LocalCount].y;
                        _x = m_NormalOriginPosition[LocalCount].x;
                        if(LocalCount % 2 == 1)
                        {
                            if(sinf(m_PhaseTime) <= 1)  //_y > .75f
                            {
                                _y -= (float)(4.2f * sinf(m_PhaseTime));
                            }
                            else
                            {
                                _y = .75f;
                            }
                        }
                        else
                        {
                            if(sinf(m_PhaseTime) <= 1) //_y > 2.25f
                            {
                                _y -= (float)(2.2f * sinf(m_PhaseTime));
                            }
                            else
                            {
                                _y = 2.25f;
                            }
                        }
                        it.getdata()->SetEnableActor(true);
                        it.getdata()->SetPosition(glm::vec3(_x, _y, _z));
                        it.getdata()->SetTarget(m_Player);
                        it.getdata()->Update(time);
                        LocalCount++;
                    }
                }
            }
            else if(m_UsedNormalEnemy->size() > 0)
            {
                if(m_RunTime <= 15) // Normal enemies stay
                {
                    uint8_t i = 0;
                    if(!m_PhaseActive[1])
                    {
                        m_PhaseTime = 0;
                        for(auto it = m_UsedNormalEnemy->begin(); it != m_UsedNormalEnemy->end(); ++it)
                        {
                            m_NormalOriginPosition[i] = it.getdata()->GetTransform()->m_Position;
                            i++;
                        }
                        uint8_t i = 0;
                        m_PhaseActive[1] = true;
                    }

                    for(auto it = m_UsedNormalEnemy->begin(); it != m_UsedNormalEnemy->end(); ++it)
                    {
                        _x = m_NormalOriginPosition[i].x;
                        _y = m_NormalOriginPosition[i].y;
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
                                m_FreeNormalEnemy->push_front(it.getdata());
                                m_UsedNormalEnemy->erase(it.get_current_node());
                            } 
                        }
                    } 
                }
            }
#pragma endregion OPENING
            else  // random spawn normal enemy
            {
                m_NormalSpawnTime -= time.GetTick();
                if(m_NormalSpawnTime <= 0)
                {
                    get = m_FreeNormalEnemy->front()->get();
                    float r_x = (float) ((rand() / (RAND_MAX + 1.f)) * 4.8f) - 2.6f;
                    glm::vec3 _Origin = glm::vec3(r_x, 5.f, -.4f);
                    get->SetPosition(_Origin);
                    get->SetOriginPosition(_Origin);
                    get->SetEnableActor(true);
                    get->GetBounding()->SetNeedTest(true);
                    m_FreeNormalEnemy->pop_front();
                    m_RandSpawnEnemy->push_back(get);
                    m_NormalSpawnTime = 3.f;
                }
                for(auto it = m_RandSpawnEnemy->begin(); it != m_RandSpawnEnemy->end(); ++it)
                {
                    it.getdata()->SetTarget(m_Player);
                    it.getdata()->Update(time);
                    it.getdata()->Behavior(time);
                    if(it.getdata()->GetTransform()->m_Position.y >= 5.1f)
                    {
                        it.getdata()->SetEnableActor(false);
                        m_FreeNormalEnemy->push_back(it.getdata());
                        m_RandSpawnEnemy->erase(it.get_current_node());
                    }
                }
            }
        }
        else if(m_RunTime <= 70) // Phase 2
        {
            m_PhaseTime += time.GetTick();
            float _x = 0;
            float _y = 0;
            float _z = m_EliteOriginPosition[0].z;
            if(!m_PhaseActive[2])
            {
                m_PhaseActive[2] = true;
                m_PhaseTime = 0;
            }
            if(m_PhaseTime <= M_PI_2)
            {
                for(int i = 0; i < ELITE_NUM; i++)
                {
                    _x = m_EliteOriginPosition[i].x;
                    _y = m_EliteOriginPosition[i].y;
                    float pre_y = m_Elite[i]->GetTransform()->m_Position.y;
                    if(i % 2 == 1)
                    {
                        _y -= (float)(2.5f * sinf(m_PhaseTime));
                        if(_y > pre_y)
                        {
                            _y = pre_y;
                        }
                    }
                    else
                    {
                        _y -= (float)(4.5f * sinf(m_PhaseTime));
                        if(_y > pre_y)
                        {
                            _y = pre_y;
                        }
                    }
                    m_Elite[i]->SetEnableActor(true);
                    m_Elite[i]->GetBounding()->SetNeedTest(true);
                    m_Elite[i]->SetPosition(glm::vec3(_x, _y, _z));
                    m_Elite[i]->Update(time);
                }
                CORE_TRACE("Phase time : {0}", m_PhaseTime);
            }
            else
            {
                if(m_RunTime <= 65)
                {
                    if(m_PhaseActive[0])
                    {
                        for(int i = 0; i < ELITE_NUM; i++)
                        {
                            m_EliteOriginPosition[i] = m_Elite[i]->GetTransform()->m_Position;
                        }
                        m_PhaseActive[0] = false;
                        CORE_TRACE("One time");
                    }
                    else
                    {
                        if(m_EliteCount > 0)
                        {
                            for(int i = 0; i < ELITE_NUM; i++)
                            {
                                if(i % 2 == 1)
                                {
                                    _x = m_EliteOriginPosition[i].x + (float)(sinf(1.5f * m_PhaseTime)) * 1.5f;
                                    _y = m_EliteOriginPosition[i].y - (float)(cosf(1.5f * m_PhaseTime) * sinf(1.5f * m_PhaseTime) * 1.25f);
                                    m_Elite[i]->SetPosition(glm::vec3(_x, _y, _z));
                                }
                                else
                                {
                                    float _sin = sinf(m_PhaseTime);
                                    float _cos = cosf(m_PhaseTime);
                                    if(i == 0)
                                    {
                                        _x = m_EliteOriginPosition[i].x - _sin;
                                        _y = m_EliteOriginPosition[i].y + _sin * _cos;
                                    }
                                    else
                                    {
                                        _x = m_EliteOriginPosition[i].x + _sin;
                                        _y = m_EliteOriginPosition[i].y + _sin * _cos;
                                    }
                                    m_Elite[i]->SetPosition(glm::vec3(_x, _y, _z));
                                }
                                m_Elite[i]->Update(time);
                            }
                        }
                    }
                }
                else
                {
                    if(m_EliteCount > 0)
                    {
                        for(int i = 0; i < ELITE_NUM; i++)
                        {
                            _x = m_Elite[i]->GetTransform()->m_Position.x;
                            _y = m_Elite[i]->GetTransform()->m_Position.y;
                            _y += time.GetTick();
                            m_Elite[i]->SetPosition(glm::vec3(_x, _y, _z));
                            m_Elite[i]->Update(time);

                            if(_y >= 4.8)
                            {
                                m_Elite[i]->SetEnableActor(false);
                            }
                        }
                    }
                }
            }
        }
        else // Boss Phase
        {
            m_PhaseTime += time.GetTick();
            float _x = 0;
            float _y = 0;
            float _z = m_Boss->GetTransform()->m_Position.z;
            if(m_RunTime < 83.5f)
            {
                if(!m_PhaseActive[0])
                {
                    _x = m_BossOriginPosition.x;
                    _y += m_Boss->GetTransform()->m_Position.y + time.GetTick() * 1.5f;
                    m_Boss->SetPosition(glm::vec3(_x, _y, _z));
                    if(_y >= 9)
                    {
                        m_PhaseActive[0] = true;
                    }
                }
                else
                {
                    if(m_PhaseActive[1])
                    {
                        m_Boss->SetScale(glm::vec3(1.f, 1.f, 1));
                        m_Boss->SetRotation(0);
                        m_Boss->SetPosition(glm::vec3(0.f, 5.f, -.4f));
                        m_PhaseTime = 0;
                        m_BossOriginPosition = m_Boss->GetTransform()->m_Position;
                        m_PhaseActive[1] = false;
                    }
                    float pre_y = m_Boss->GetTransform()->m_Position.y;
                    _x = m_BossOriginPosition.x;
                    _y = m_BossOriginPosition.y - (float)(sinf(m_PhaseTime) * 2.5f);
                    if(_y > pre_y)
                    {
                        _y = pre_y;
                    }
                    m_Boss->SetPosition(glm::vec3(_x, _y, m_BossOriginPosition.z));
                }
            }
            else
            {
                if(m_PhaseActive[2])
                {
                    m_BossOriginPosition = m_Boss->GetTransform()->m_Position;
                    m_PhaseTime = 0;
                    m_PhaseActive[2] = false;
                }
                if(m_Boss->GetHP() >= 40)
                {
                    this->m_Boss->GetBounding()->SetNeedTest(true);
                    this->m_Boss->Behavior(time);
                }
                else
                {
                    if(m_PhaseActive[0])
                    {
                        this->m_Boss->GetBounding()->SetNeedTest(false);
                        this->m_Boss->CanAttack(false);
                        m_PhaseTime = 0;
                        m_BossSecondStateCal = m_BossOriginPosition - m_Boss->GetTransform()->m_Position;
                        m_BossOriginPosition = m_Boss->GetTransform()->m_Position;
                        m_PhaseActive[0] = false;
                    }
                    if(m_PhaseTime <= M_PI_2)
                    {
                        _x = m_BossOriginPosition.x + (float)(sinf(m_PhaseTime) * m_BossSecondStateCal.x) ;
                        _y = m_BossOriginPosition.y + (float)(sinf(m_PhaseTime) * m_BossSecondStateCal.y) ;
                        m_Boss->SetPosition(glm::vec3(_x, _y, m_BossOriginPosition.z));
                    }
                    else if(m_Boss->GetHP() > 0)
                    {
                        this->m_Boss->GetBounding()->SetNeedTest(true);
                        this->m_Boss->Behavior(time);
                    }
                    else
                    {
                        b_GameOver = true;
                    }
                }
            }
            m_Boss->SetTarget(m_Player);
            m_Boss->SetEnableActor(true);
            m_Boss->Update(time);
        }
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
                if(it.getdata()->GetID() == Projectile::TeamID::Player)
                {
                    it.getdata()->GetBounding()->SetNeedTest(true);
                    for(auto n_it = m_UsedNormalEnemy->begin(); n_it != m_UsedNormalEnemy->end(); ++n_it)
                    {
                        if(n_it.getdata()->GetBounding()->IsNeedTest())
                        {
                            if(it.getdata()->GetBounding()->Intersects(n_it.getdata()->GetBounding()))
                            {
                                n_it.getdata()->TakeDamage();
                                if(n_it.getdata()->GetHP() <= 0)
                                {
                                    n_it.getdata()->SetEnableActor(false);
                                    n_it.getdata()->GetBounding()->SetNeedTest(false);
                                    m_FreeNormalEnemy->push_back(n_it.getdata());
                                    m_UsedNormalEnemy->erase(n_it.get_current_node());
                                }
                                it.getdata()->GetBounding()->SetNeedTest(false);
                                it.getdata()->SetTeamID(Projectile::TeamID::Neutral);
                                ProSystem->GetUsedList()->erase(it.get_current_node());
                                ProSystem->GetFreeList()->push_back(it.getdata());
                            }
                        }
                    }

                    for(auto n_it = m_RandSpawnEnemy->begin(); n_it != m_RandSpawnEnemy->end(); ++n_it)
                    {
                        if(n_it.getdata()->GetBounding()->IsNeedTest())
                        {
                            if(it.getdata()->GetBounding()->Intersects(n_it.getdata()->GetBounding()))
                            {
                                n_it.getdata()->TakeDamage();
                                if(n_it.getdata()->GetHP() <= 0)
                                {
                                    n_it.getdata()->SetEnableActor(false);
                                    n_it.getdata()->GetBounding()->SetNeedTest(false);
                                    m_FreeNormalEnemy->push_back(n_it.getdata());
                                    m_RandSpawnEnemy->erase(n_it.get_current_node());
                                }
                                it.getdata()->GetBounding()->SetNeedTest(false);
                                it.getdata()->SetTeamID(Projectile::TeamID::Neutral);
                                ProSystem->GetUsedList()->erase(it.get_current_node());
                                ProSystem->GetFreeList()->push_back(it.getdata());
                            }
                        }
                    }
                    
                    for(int i = 0; i < ELITE_NUM; i++)
                    {
                        if(m_Elite[i]->GetBounding()->IsNeedTest())
                        {
                            if(m_Elite[i]->GetBounding()->Intersects(it.getdata()->GetBounding()))
                            {
                                m_Elite[i]->TakeDamage();
                                if(m_Elite[i]->GetHP() <= 0)
                                {
                                    m_Elite[i]->SetEnableActor(false);
                                    m_Elite[i]->GetBounding()->SetNeedTest(false);
                                }
                                it.getdata()->GetBounding()->SetNeedTest(false);
                                it.getdata()->SetTeamID(Projectile::TeamID::Neutral);
                                ProSystem->GetUsedList()->erase(it.get_current_node());
                                ProSystem->GetFreeList()->push_back(it.getdata());
                            }
                        }
                    }

                    if(m_Boss->GetBounding()->IsNeedTest())
                    {
                        if(m_Boss->GetBounding()->Intersects(it.getdata()->GetBounding()))
                        {
                            m_Boss->TakeDamage();
                            if(m_Boss->GetHP() <= 0)
                            {
                                b_GameOver = true;
                            }
                            it.getdata()->GetBounding()->SetNeedTest(false);
                            it.getdata()->SetTeamID(Projectile::TeamID::Neutral);
                            ProSystem->GetUsedList()->erase(it.get_current_node());
                            ProSystem->GetFreeList()->push_back(it.getdata());
                            CORE_INFO("Hit Boss HP : {0}", m_Boss->GetHP());
                        }
                    }
                }
                else if(it.getdata()->GetID() == Projectile::TeamID::Enemy)
                {
                    it.getdata()->GetBounding()->SetNeedTest(true);
                    if(m_Player->GetBounding()->Intersects(it.getdata()->GetBounding()))
                    {
                        m_Player->TakeDamage();
                        it.getdata()->GetBounding()->SetNeedTest(false);
                        it.getdata()->SetTeamID(Projectile::TeamID::Neutral);
                        ProSystem->GetUsedList()->erase(it.get_current_node());
                        ProSystem->GetFreeList()->push_back(it.getdata());
                        CORE_INFO("Hit player");
                    }
                }
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