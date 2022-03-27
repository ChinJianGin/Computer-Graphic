#include"Core.h"

namespace CustomSpace
{
    class PerspectiveCamera
    {
        public:
            PerspectiveCamera(float fov, GLfloat aspect, float near, float far);
        private:

            glm::mat4 m_ProjectionMatrix;
    };
}