#include"../include/PerspectiveCamera.h"

namespace CustomSpace
{
    PerspectiveCamera::PerspectiveCamera(float fov, GLfloat aspect, float near, float far)
    : m_ProjectionMatrix(glm::perspective(glm::radians(fov), aspect, near, far))
    {
        m_View = glm::lookAt(m_Position, m_Position + m_LookAt, m_UpVector);
        m_VP = m_ProjectionMatrix * m_View;        
    }

    void PerspectiveCamera::SetProjecttion(float fov, float aspectratio, float near, float far)
    {
        m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectratio, near, far);
        m_VP = m_ProjectionMatrix * m_View;
    }

    void PerspectiveCamera::SetPosition(const glm::vec3& pos)
    {
        m_Position = pos;
        m_View = glm::lookAt(m_Position, m_Position + m_LookAt, m_UpVector);
        m_VP = m_ProjectionMatrix * m_View;
    }

    void PerspectiveCamera::SetLookAt(const glm::vec3& look)
    {
        m_LookAt = look;
        m_View = glm::lookAt(m_Position, m_Position + m_LookAt, m_UpVector);
        m_VP = m_ProjectionMatrix * m_View;
    }
}