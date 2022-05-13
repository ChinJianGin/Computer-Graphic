#include"../include/OrthoCamera.h"

namespace CustomSpace
{
    OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
    : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, near, far))
    {
        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthoCamera::SetProjection(float left, float right, float bottom, float top, float near, float far)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, near, far);
        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void OrthoCamera::LocalUpdate()
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.f), m_Position) * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);
        m_VPMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}