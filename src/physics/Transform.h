#pragma once
#include"../core/include/Core.h"

namespace CustomSpace
{
    class Transform
    {
        public:
        Transform(
            const glm::vec3& pos = glm::vec3(0.f),
            const glm::vec3& axis = glm::vec3(0, 0, 1.f),
            const glm::vec3& scale = glm::vec3(1.f, 1.f, 1.f),
            float radian = 0.f);
        

        virtual void SetModelMatrix(const glm::mat4& model);

        virtual void SetPosition(const glm::vec3& pos);
        virtual void SetRotation(const float radian, const glm::vec3& axis);
        virtual void SetScaleValue(const glm::vec3& scale);

        virtual void SetParentTransform(const Ref<Transform>& parent);

        const virtual glm::mat4& GetModelMatrix() const;
        const virtual glm::mat4& GetTranslate() const;
        const virtual glm::mat4& GetRotate() const;
        const virtual glm::mat4& GetScale() const;

        const virtual glm::vec3& GetLocalPosition() const;
        const virtual glm::vec3& GetWorldPosition() const;

        const virtual glm::quat& GetQuaternion() const;
        private:
        protected:
        glm::mat4 m_ModelMatrix;
        glm::mat4 m_Translate;
        glm::mat4 m_Rotate;
        glm::mat4 m_Scale;

        glm::vec3 m_Position;
        mutable glm::vec3 m_WorldPosition;
        glm::vec3 m_Axis;
        glm::vec3 m_ScaleValue;
        glm::vec3 m_Skew;
        glm::vec4 m_Perspective;

        glm::quat m_QuatRotation;

        float m_Radian;

        Ref<Transform> m_ParentTransform = nullptr;
    };
}