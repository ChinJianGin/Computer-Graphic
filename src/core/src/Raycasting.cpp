#include"../include/Raycasting.h"

namespace CustomSpace
{
    Raycasting::Raycasting(PerspectiveCamera& cam, const int width, const int height)
    {
        m_Width = width; m_Height = height;
        m_Camera = &cam;
    }

    Raycasting::~Raycasting()
    {

    }

    void Raycasting::Update(CoreTimer& timer)
    {
        m_CurrentRay = CalCurrentRay();
    }

    const glm::vec3& Raycasting::GetCurrentRay()
    {
        return m_CurrentRay;
    }

    const glm::vec3 Raycasting::CalCurrentRay()
    {
        // float mouse_x = Input::MouseX; float mouse_y = Input::MouseY;
        // if(mouse_x >= m_Width / 2) mouse_x = m_Width / 2;
        // else if(mouse_x <= 0) mouse_x = 0;
        // if(mouse_y >= m_Height / 2) mouse_y = m_Height / 2;
        // else if(mouse_y <= 0) mouse_y = 0;
        // float x = (2.f * mouse_x) / m_Width - 1.f;
        // float y = 1.f - (2.f * mouse_y) / m_Height;
        glm::vec2 ray_nds = glm::vec2(0, 0);

        glm::vec4 ray_clip = glm::vec4(ray_nds.x, ray_nds.y, -1.f, 1.f);

        glm::vec4 ray_eye = glm::inverse(m_Camera->GetProjectionMatrix()) * ray_clip;
        ray_eye = glm::vec4(ray_eye.x, ray_eye.y, -1.f, 0.f);

        glm::vec3 ray_wor = glm::vec3(glm::inverse(m_Camera->GetViewMatrix()) * ray_eye);
        ray_wor = glm::normalize(ray_wor);

        return ray_wor;
    }

    void Raycasting::SetWindowSize(const int width, const int height)
    {
        m_Width = width; m_Height = height;
    }
}