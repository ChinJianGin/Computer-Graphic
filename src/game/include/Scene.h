#pragma once
#include "../../core/include/Core.h"
#include "../../core/include/Timer.h"
#include "../../graphic/Renderer.h"
#include"../../client/include/Creator.h"
#include "../../graphic/Texture.h"
#include "./Player.h"
#include "./ProjectileSystem.h"
#include "../../core/include/KeyEvent.h"
#include "./NormalEnemy.h"
#include "./EliteEnemy.h"
#include "./BossEnemy.h"


constexpr uint8_t NORMAL_NUM = 20;
constexpr uint8_t ELITE_NUM = 3;

namespace CustomSpace
{
    class Scene
    {
        public:
            Scene();
            ~Scene();

            void Init();
            void Update(CoreTimer& time);

            bool OnKeyPressedEvent(KeyPressedEvent& event);
            void OnEvent(Event& event);

        private:
            Ref<Shape> m_Background, m_Background2;
            Ref<Texture2D> m_Texture, m_Texture2, m_Projectile[2];
            Ref<APlayer> m_Player;

            Ref<ShapeFactory> m_Factory;

            glm::vec3 m_OriginTransform[3];
            float m_FrameTime = 0, m_MoveSpeed = (9.6 / 20);
            float m_RunTime = 0;
            float m_PhaseTime = 0;
            float m_NormalSpawnTime = 3.f;

            glm::vec3 m_Transform;
            float m_PlayerSpeed = 1.5f;

            Ref<Enemy> m_Elite[ELITE_NUM], m_Boss;
            Ref<Enemy> m_Normals[NORMAL_NUM];

            Scope<SinglyLinkedList<Ref<Enemy>>> m_UsedNormalEnemy, m_FreeNormalEnemy, m_RandSpawnEnemy;

            glm::vec3 m_NormalOriginPosition[NORMAL_NUM] = { glm::vec3(0) };
            glm::vec3 m_EliteOriginPosition[ELITE_NUM] = { glm::vec3(0) };
            glm::vec3 m_BossOriginPosition = glm::vec3(0);

            bool m_PhaseActive[3] = { false };
            uint8_t m_EliteCount = ELITE_NUM;
        protected:

    };
}