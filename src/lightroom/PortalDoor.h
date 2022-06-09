#pragma once
#include"./LActor.h"
#include"../graphic/ModelLoad/Model.h"

namespace CustomSpace
{
    class PortalDoor : public LActor
    {
        public:
        PortalDoor();

        ~PortalDoor() = default;
        virtual void Init() override;

        virtual void Update(CoreTimer& timer) override;

        virtual void SetModelMatrix(glm::mat4& model) override;
        virtual void SetPosition(glm::vec3& pos) override;
        virtual void SetRotation(float radians, glm::vec3& axis) override;
        virtual void SetScale(glm::vec3& scale) override;
        virtual void SetParent(Ref<Transform>& parent) override;

        private:

        void LocalUpdate();

        Ref<Model> m_Model[3];

        glm::mat4 m_local_left, m_local_right;

        bool b_IsDirty = false;
    };
}