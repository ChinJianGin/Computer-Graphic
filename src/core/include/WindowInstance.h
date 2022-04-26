#pragma once
#include"Window.h"

namespace CustomSpace
{
    class WindowInstance : public Windows
    {
        public:
            WindowInstance(const WindowProps& proprs);
            virtual ~WindowInstance();

            void Update() override;

            unsigned int GetWidth() const override { return M_Prop.Width; }
            unsigned int GetHeight() const override { return M_Prop.Height; }

            void SetupMainCallbacks() override;
            void SetEventCallback(const EventCallbackFn& callback) override { M_Prop.EventCallback = callback; }
            void SetVSync(bool  enable) override;
            bool IsVSync() const override;

            virtual void* GetWindow() const { return M_Window; }

        private:
            virtual void Init(const WindowProps& props);
            virtual void Shutdown();
            GLFWwindow* M_Window;
            Scope<OpenGLContext> M_Context;

            WindowProps M_Prop;
    };
}