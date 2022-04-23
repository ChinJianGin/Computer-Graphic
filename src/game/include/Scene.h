#pragma once
#include "../../core/include/Core.h"
#include "../../core/include/Timer.h"
#include "../../graphic/Renderer.h"
#include"../../client/include/Creator.h"
#include "../../graphic/Texture.h"

namespace CustomSpace
{
    class Scene
    {
        public:
            Scene();
            ~Scene();

            void Init();
            void Update(CoreTimer& time);
        private:
            CustomSpace::Ref<CustomSpace::Shape> m_Background, m_Background2;
            CustomSpace::Ref<CustomSpace::Texture2D> m_Texture, m_Texture2;

            CustomSpace::Ref<CustomSpace::ShapeFactory> m_Factory;

            glm::vec3 m_OriginTransform[3];
            float m_FrameTime = 0, m_MoveSpeed = (9.6 / 20);
        protected:

    };
}