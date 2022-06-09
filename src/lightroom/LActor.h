#pragma once
#include"../core/include/Core.h"
#include"../physics/Transform.h"

namespace CustomSpace
{
    class LActor
    {
        public:

        virtual void Init() = 0;

        virtual void Update(CoreTimer& timer) = 0;

        virtual Ref<Transform>& GetTransform() { return this->m_Transform; }

        virtual void SetModelMatrix(glm::mat4& model) { m_Transform->SetModelMatrix(model); }
        virtual void SetPosition(glm::vec3& pos) { m_Transform->SetPosition(pos); }
        virtual void SetRotation(float radians, glm::vec3& axis) { m_Transform->SetRotation(radians, axis); }
        virtual void SetScale(glm::vec3& scale) { m_Transform->SetScaleValue(scale); }
        virtual void SetParent(Ref<Transform>& parent) { m_Transform->SetParentTransform(parent); }
        protected:
        Ref<Transform> m_Transform;
    };
}