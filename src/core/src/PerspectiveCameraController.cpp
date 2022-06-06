#include "../include/PerspectiveCameraController.h"
// #include "../../lightscene/include/3DScene.h"
#include "../../lightscene/include/Room.h"
namespace CustomSpace
{
    PerspectiveCameraController::PerspectiveCameraController(int width, int height, glm::vec3 &pos) : m_Width(width), m_Height(height), m_CameraPostition(pos)
    {
        m_AspectRatio = (float)m_Width / m_Height;
        m_Camera = new PerspectiveCamera(60, m_AspectRatio, 1.f, 1000.f);
        m_Camera->SetPosition(m_CameraPostition);
        m_Yaw = -90.f;
        m_Pitch = 0.f;
        m_Sensitivity = .1f;
    }

    PerspectiveCameraController::PerspectiveCameraController(int width, int height, float fov, float near, float far, glm::vec3 &pos) : m_Width(width), m_Height(height), m_CameraPostition(pos)
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

    void PerspectiveCameraController::Update(CoreTimer &timer)
    {
    }

    void PerspectiveCameraController::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT(PerspectiveCameraController::OnMouseInput));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(PerspectiveCameraController::OnMouseMoved));
        dispatcher.Dispatch<MouseScrollEvent>(BIND_EVENT(PerspectiveCameraController::OnMouseScrolled));
    }

    void PerspectiveCameraController::OnResize(int width, int height)
    {
    }

    bool PerspectiveCameraController::OnMouseInput(MouseButtonPressedEvent &event)
    {
        if (event.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT && !b_Reset)
        {
            glfwSetInputMode((GLFWwindow *)LightTestRoom::Get().GetWindow().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            m_LastX = Input::MouseX;
            m_LastY = Input::MouseY;
            b_Reset = true;
        }
        else
        {
            if (event.GetMouseButton() == GLFW_MOUSE_BUTTON_RIGHT && b_Reset)
            {
                glfwSetInputMode((GLFWwindow *)LightTestRoom::Get().GetWindow().GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                b_Reset = false;
            }
        }

        return false;
    }

    bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent &event)
    {
        if (b_Reset)
        {
            float x_offset = Input::MouseX - m_LastX;
            float y_offset = m_LastY - Input::MouseY;

            m_LastX = Input::MouseX;
            m_LastY = Input::MouseY;

            x_offset *= m_Sensitivity;
            y_offset *= m_Sensitivity;

            m_Yaw += x_offset;
            m_Pitch += y_offset;

            if (m_Pitch > 89.f)
                m_Pitch = 89.f;
            if (m_Pitch < -89.f)
                m_Pitch = -89.f;

            b_LookAtUpdate = true;
            this->LocalUpdate();
        }
        return false;
    }

    bool PerspectiveCameraController::OnMouseScrolled(MouseScrollEvent& event)
    {
        m_ZoomLevel -= (float)event.GetYOffset();
        b_ZoomUpdate = true;
        if(m_ZoomLevel < 1.f)
            m_ZoomLevel = 1.f;
        if(m_ZoomLevel > 45.f)
            m_ZoomLevel = 45.f;
        
        this->LocalUpdate();
        return false;
    }

    void PerspectiveCameraController::LocalUpdate()
    {
        if(b_LookAtUpdate)
        {
            glm::vec3 look_at;
            look_at.x = cosf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch));
            look_at.y = sinf(glm::radians(m_Pitch));
            look_at.z = sinf(glm::radians(m_Yaw)) * cosf(glm::radians(m_Pitch));
            m_Camera->SetLookAt(look_at);
            b_LookAtUpdate = false;
        }

        if(b_ZoomUpdate)
        {
            m_Camera->SetProjecttion(m_ZoomLevel, m_AspectRatio, .1f, 1000.f);
            b_ZoomUpdate = false;
        }
    }
}