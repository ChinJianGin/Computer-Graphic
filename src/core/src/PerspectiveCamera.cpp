#include"../include/PerspectiveCamera.h"

namespace CustomSpace
{
    PerspectiveCamera::PerspectiveCamera(float fov, GLfloat aspect, float near, float far)
    : m_ProjectionMatrix(glm::perspective(fov, aspect, near, far))
    {
        
    }
}