#include"../include/PerspectiveCameraController.h"

namespace CustomSpace
{
    PerspectiveCameraController::PerspectiveCameraController(int width, int height, glm::vec3& pos) : m_Width(width), m_Height(height), m_CameraPostition(pos)
    {
        m_AspectRatio = (float)m_Width / m_Height;
        m_Camera = new PerspectiveCamera(60, m_AspectRatio, 1.f, 1000.f);
        m_Camera->SetPosition(m_CameraPostition);
        m_Yaw = -90.f;
        m_Pitch = 0.f;
        m_Sensitivity = .1f;
    }

    PerspectiveCameraController::PerspectiveCameraController(int width, int height, float fov, float near, float far, glm::vec3& pos) : m_Width(width), m_Height(height), m_CameraPostition(pos)
    {
        m_AspectRatio = (float)m_Width / m_Height;
        m_Camera = new PerspectiveCamera(fov, m_AspectRatio, near, far);
        m_Camera->SetPosition(m_CameraPostition);
        m_Yaw = -90.f;
        m_Pitch = 0.f;
        m_Sensitivity = .1f;
    }

    PerspectiveCameraController::~PerspectiveCameraController()
    {
        delete m_Camera;
    }

    void PerspectiveCameraController::Update(CoreTimer& timer)
    {
        if(!b_First)
        {
            m_LastX = Input::MouseX;
            m_LastY = Input::MouseY;
            b_First = true;
        }
        float x_offset = Input::MouseX - m_LastX;
        float y_offset = m_LastY - Input::MouseY;

        m_LastX = Input::MouseX;
        m_LastY = Input::MouseY;

        x_offset *= m_Sensitivity;
        y_offset *= m_Sensitivity;

        m_Yaw += x_offset;
        m_Pitch += y_offset;

        if(m_Pitch > 89.f)
            m_Pitch = 89.f;
        if(m_Pitch < -89.f)
            m_Pitch = -89.f;

        this->LocalUpdate();
    }

    void PerspectiveCameraController::OnEvent(Event& event)
    {

    }

    void PerspectiveCameraController::OnResize(int width, int height)
    {

    }

    void PerspectiveCameraController::LocalUpdate()
    {
        glm::vec3 look_at;
        look_at.x = cosf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch));
        look_at.y = sinf(glm::radians(m_Pitch));
        look_at.z = sinf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch));
        m_Camera->SetLookAt(look_at);
    }
}