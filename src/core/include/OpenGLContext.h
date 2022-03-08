#pragma once

#include"Core.h"

namespace CustomSpace
{
    class OpenGLContext : public RenderContext
    {
        public:
            OpenGLContext(GLFWwindow*  window);

            void Init() override;
            void SwapBuffers() override;

            static Scope<OpenGLContext> Create(void* window);
        private:
            GLFWwindow* M_Window;
    };
}