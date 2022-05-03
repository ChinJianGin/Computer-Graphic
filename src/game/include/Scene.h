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
            Ref<Shape> m_Background, m_Background2, m_CollisionTest;
            Ref<Texture2D> m_Texture, m_Texture2;
            Ref<APlayer> m_Player;

            Ref<ShapeFactory> m_Factory;

            glm::vec3 m_OriginTransform[3];
            float m_FrameTime = 0, m_MoveSpeed = (9.6 / 20);
            float m_RunTime = 0;


            glm::vec3 m_Transform;
            float m_PlayerSpeed = 1.f;

            Ref<Enemy> m_Normal;
        protected:

    };
}