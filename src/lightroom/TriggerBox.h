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

        Ref<Transform> GetTransform() { return this->m_Transform; }

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
        Ref<Transform> m_Transform;
        glm::vec3 m_TR, m_BL;
        bool b_Overlap = false;
    };
}