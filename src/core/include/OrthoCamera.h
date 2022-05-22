#pragma once
#include"Core.h"

namespace CustomSpace
{
    class OrthoCamera
    {
        public:
            OrthoCamera(int width, int hieght, float left, float right, float bottom, float top, float near = -1.f, float far = 1.f);
            ~OrthoCamera() = default;

            void SetPosition(const glm::vec3& position) { m_Position = position; LocalUpdate(); }
            void SetRotation(float rotation) { m_Rotation = rotation; LocalUpdate(); }

            void SetProjection(float left, float right, float bottom, float top, float near = -1.f, float far = 1.f);
            void SetProjection(unsigned int width, unsigned int height, float left, float right, float bottom, float top, float near = -1.f, float far = 1.f);

            const glm::vec3& GetPosition() const { return m_Position; }
            float GetRotation() const { return m_Rotation; }

            const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
            const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
            const glm::mat4& GetVPMatrix() const { return m_VPMatrix; }
        private:
            glm::mat4 m_ViewMatrix = glm::inverse(glm::mat4(1.f));
            glm::mat4 m_ProjectionMatrix;
            glm::mat4 m_VPMatrix;

            glm::vec3 m_Position = { 0.f, 0.f, 0.f };
            float m_Rotation = 0.f;

            float m_AspectRatio = 0;

            void LocalUpdate();
    };
}