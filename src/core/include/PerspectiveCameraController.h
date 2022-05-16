#pragma once
#include"./Core.h"
#include"./PerspectiveCamera.h"
#include"./Event.h"

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

        PerspectiveCamera& GetCamera() { return *this->m_Camera; }
        const PerspectiveCamera& GetCamera() const { return *this->m_Camera; }
        private:
        int m_Width, m_Height;
        float m_AspectRatio;

        PerspectiveCamera* m_Camera;

        glm::vec3 m_CameraPostition = glm::vec3(0);

        float m_LastX, m_LastY, m_Yaw, m_Pitch, m_Sensitivity, m_ZoomLevel = 1.f;

        void LocalUpdate();

        bool b_First = false;
    };
}