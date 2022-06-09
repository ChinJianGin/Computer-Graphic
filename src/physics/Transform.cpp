#include"./Transform.h"

namespace CustomSpace
{
    Transform::Transform(
        const glm::vec3 &pos,
        const glm::vec3 &axis,
        const glm::vec3 &scale,
        float radian) : m_Position(pos), m_Axis(axis), m_ScaleValue(scale), m_Radian(radian)
    {
        m_Translate = glm::translate(glm::mat4(1.f), m_Position);
        m_Rotate = glm::rotate(glm::mat4(1.f), m_Radian, m_Axis);
        m_QuatRotation = glm::toQuat(m_Rotate);
        m_Scale = glm::scale(glm::mat4(1.f), m_ScaleValue);
        m_ModelMatrix = m_Translate * m_Rotate * m_Scale;
    }

    void Transform::SetParentTransform(const Ref<Transform>& parent)
    {
        m_ParentTransform = parent;
    }

    void Transform::SetModelMatrix(const glm::mat4& model)
    {
        if(m_ParentTransform == nullptr)
            m_ModelMatrix = model;
        else
            m_ModelMatrix = m_ParentTransform->GetModelMatrix() * model;
        glm::decompose(m_ModelMatrix, m_ScaleValue, m_QuatRotation, m_Position, m_Skew, m_Perspective);
    }

    void Transform::SetPosition(const glm::vec3& pos)
    {
        m_Position = pos;
        m_Translate = glm::translate(glm::mat4(1.f), m_Position);
    }

    void Transform::SetRotation(const float radian, const glm::vec3& axis)
    {
        m_Radian = radian;
        m_Axis = axis;
        m_QuatRotation = glm::angleAxis(m_Radian, m_Axis);
        // m_Rotate = glm::toMat4(m_QuatRotation);
        m_Rotate = glm::rotate(glm::mat4(1.f), glm::radians(radian), axis);
    }

    void Transform::SetScaleValue(const glm::vec3& scale)
    {
        m_ScaleValue = scale;
        m_Scale = glm::scale(glm::mat4(1.f), scale);
    }

    const glm::mat4& Transform::GetModelMatrix() const
    {
        return m_ModelMatrix;
    }

    const glm::mat4& Transform::GetTranslate() const
    {
        return m_Translate;
    }

    const glm::mat4& Transform::GetRotate() const
    {
        return m_Rotate;
    }

    const glm::mat4& Transform::GetScale() const
    {
        return m_Scale;
    }

    const glm::vec3& Transform::GetLocalPosition() const
    {
        return m_Position;
    }

    const glm::vec3& Transform::GetWorldPosition() const
    {
        m_WorldPosition = glm::vec3(m_ModelMatrix * glm::vec4(m_Position, 1.f));
        return m_WorldPosition;
    }

    const glm::quat& Transform::GetQuaternion() const
    {
        return m_QuatRotation;
    }
}