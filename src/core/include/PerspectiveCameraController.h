#pragma once
#include"./Core.h"
#include"./PerspectiveCamera.h"
#include"./Event.h"
#include"./MouseEvent.h"
#include"./Raycasting.h"

namespace CustomSpace
{
    class PerspectiveCameraController
    {
        public:
        PerspectiveCameraController(int width, int height, glm::vec3& pos);
        PerspectiveCameraController(int width, int height, float fov, float near, float far, glm::vec3& pos);
        ~PerspectiveCameraController();

        void Update(CoreTimer& timer);
        void OnEvent(Event& event);

        void OnResize(int width, int height);

        bool OnMouseInput(MouseButtonPressedEvent& event);
        bool OnMouseMoved(MouseMovedEvent& event);
        bool OnMouseScrolled(MouseScrollEvent& event);

        PerspectiveCamera& GetCamera() { return *this->m_Camera; }
        const PerspectiveCamera& GetCamera() const { return *this->m_Camera; }
        const glm::vec3& GetCurrentRay() const { return this->m_Raycasting->GetCurrentRay(); }
        private:
        int m_Width, m_Height;
        float m_AspectRatio;

        PerspectiveCamera* m_Camera;

        glm::vec3 m_CameraPostition = glm::vec3(0);

        float m_LastX, m_LastY, m_Yaw, m_Pitch, m_Sensitivity, m_ZoomLevel = 1.f;

        void LocalUpdate();

        Scope<Raycasting> m_Raycasting;

        bool b_Reset = false, b_ZoomUpdate = false, b_LookAtUpdate = false;

    };
}