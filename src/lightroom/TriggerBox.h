#pragma once
#include"../core/include/Core.h"
#include"../graphic/LightBox.h"

namespace CustomSpace
{
    class TriggerBox
    {
        public:
        TriggerBox();
        ~TriggerBox();

        void Init();

        const Ref<Transform> GetTransform() { return m_Body->GetTransform(); }

        void SetPosition(const glm::vec3& pos);
        void SetScale(const glm::vec3& scale);
        void SetModelMatrix(const glm::mat4& model);

        void Update(CoreTimer& timer);

        bool BeginOverlap(const glm::vec3& pos);
        bool EndOverlap(const glm::vec3& pos);

        Ref<Shape>& GetBody() { return this->m_Body; }

        const glm::vec3& GetTR() const { return this->m_TR; }
        const glm::vec3& GetBL() const { return this->m_BL; }

        private:
        Ref<Shape> m_Body;
        glm::vec3 m_TR, m_BL;
        bool b_Overlap = false;
    };
}