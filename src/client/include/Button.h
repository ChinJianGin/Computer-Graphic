#pragma once
#include"../../core/include/Core.h"
#include"../include/Creator.h"

namespace CustomSpace
{
    class Button
    {
        public:
            Button();
            ~Button() = default;

            void Init();
            void OnUpdate(CoreTimer& timer);

            bool OnClicked(const glm::vec2& cpos);
            bool OnHover(const glm::vec2& hpos);


            void SetPosition(const glm::vec3& pos);
            void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1));
            void SetScale(const glm::vec3& scale);
            void SetModelMatrix(const glm::mat4& model);
            void SetParentTransform(const Ref<Transform>& parent);

            const Ref<Shape>& GetBody() const { return this->m_Body; }
        private:
            Ref<Shape> m_Body;
            glm::vec3 m_OriginLB, m_OriginRT, m_WorldLB, m_WorldRT;
    };
}