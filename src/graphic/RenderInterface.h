#pragma once

#include"../core/include/Core.h"
#include"../vertex/VAO.h"

namespace CustomSpace
{
    class RenderInterface
    {
        public:
            virtual void Init() = 0;
            virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
            virtual void SetClearColor(const glm::vec4& color) = 0;
            virtual void Clear() = 0;

            virtual void DrawElement(const Ref<VAO>& vao, uint32_t count = 0) = 0;

            static Scope<RenderInterface> Create();
    };
}