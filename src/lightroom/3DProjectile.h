#pragma once
#include"../core/include/Core.h"
#include"../physics/Transform.h"
#include"../graphic/Shape.h"

namespace CustomSpace
{
    class Bullet
    {
        public:
        Bullet();
        ~Bullet();

        void Init();
        void Update(CoreTimer& timer);

        const Ref<Transform> GetTransform() { return m_Body->GetTransform(); }
        const glm::vec3& GetCurrentPos() const { return this->m_CurrentPos; }
        const Ref<Shape> GetBody() const { return this->m_Body; }

        void SetPosition(const glm::vec3& pos);
        void SetRotation(const float radians, const glm::vec3& axis);
        void SetScale(const glm::vec3& scale);
        void SetModelMatrix(const glm::mat4& model);

        void SetDirection(const glm::vec3& direct);
        void SetAcceleration(const float acceleration);

        void Reset();

        private:
        Ref<Shape> m_Body;        

        glm::vec3 m_CurrentPos, m_OriginPos;
        glm::vec3 m_Direction;
        float m_Acceleration, m_RunTime;
    };
}