#pragma once
#include"./RenderInterface.h"
namespace CustomSpace
{
    class RenderCommand
    {
        public:
            static void Init()
            {
                m_RenderInterface->Init();
            }

            static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
            {
                m_RenderInterface->SetViewport(x, y, width, height);
            }

            static void SetClearColor(const glm::vec4& color)
            {
                m_RenderInterface->SetClearColor(color);
            }

            static void Clear()
            {
                m_RenderInterface->Clear();
            }

            static void RenderTarget(const Ref<VAO>& vao, uint32_t count = 0)
            {
                m_RenderInterface->DrawElement(vao, count);
            }

            static void RenderLine(const Ref<VAO>& vao, uint32_t count = 0)
            {
                m_RenderInterface->DrawLine(vao, count);
            }

        private:
            static Scope<RenderInterface> m_RenderInterface;

    };
}