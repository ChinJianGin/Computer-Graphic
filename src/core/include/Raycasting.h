#pragma once
#include "./Core.h"
#include"./PerspectiveCamera.h"

namespace CustomSpace
{
    class Raycasting
    {
    public:
        Raycasting(PerspectiveCamera& cam, const int width, const int hegiht);
        ~Raycasting();

        void Update(CoreTimer& timer);

        void SetWindowSize(const int width, const int height);

        const glm::vec3& GetCurrentRay();
    private:
        const glm::vec3 CalCurrentRay();


        PerspectiveCamera* m_Camera;
        glm::vec3 m_CurrentRay;

        int m_Width, m_Height;
    };
}