#include"Core.h"

namespace CustomSpace
{
    class PerspectiveCamera
    {
        public:
            PerspectiveCamera(float fov, GLfloat aspectRatio, float near, float far);
            ~PerspectiveCamera() = default;

            void SetPosition(const glm::vec3& pos);
            void SetLookAt(const glm::vec3& look);

            void SetProjecttion(float fov, float aspectRatio, float near, float far);

            const glm::mat4& GetProjectionMatrix() const { return this->m_ProjectionMatrix; }
            const glm::mat4& GetViewMatrix() const { return this->m_View; }
            const glm::mat4& GetVPMatrix() const { return this->m_VP; }
        private:

            glm::mat4 m_ProjectionMatrix;
            glm::mat4 m_View;
            glm::mat4 m_ViewInv;
            glm::mat4 m_VP;

            glm::vec3 m_Position = glm::vec3(0, 0, 0);
            glm::vec3 m_LookAt = glm::vec3(0, 0, -1.f);
            glm::vec3 m_UpVector = glm::vec3(0, 1.f, 0);

            void LocalUpdate();
    };
}