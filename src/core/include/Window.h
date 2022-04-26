#pragma once

#include "Core.h"
#include"./RenderContext.h"
#include"./OpenGLContext.h"
#include"./Event.h"
namespace CustomSpace
{
    using EventCallbackFn = std::function<void(Event&)>;
    struct WindowProps
    {
        const char* Title;
        uint32_t Width;
        uint32_t Height;
        bool FullScreenMode;
        bool VSync;
        EventCallbackFn EventCallback;

        WindowProps(uint32_t width = 512, uint32_t height = 512, const char* title = "Game", bool ScreenMode = false, bool vsync  =  true):
        Width(width), Height(height), Title(title), FullScreenMode(ScreenMode), VSync(vsync)
        {

        }
    };
    struct Window
    {
        GLFWwindow* _Window;
        
        int WindowWidth;
        int WindowHeight;

        void SetupMainCallbacks();
        void Close();

        static Window* CreateWindow(int width, int height, const char* title, bool fullScreenMode = false);
        static void FreeWindow(Window* window);
    };
    class Windows
    {
        public:
            virtual ~Windows() = default;

            virtual void Update() = 0;

            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;

            virtual void SetupMainCallbacks() = 0;
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool enable) = 0;
            virtual bool IsVSync() const = 0;

            virtual void* GetWindow() const = 0;

            static Scope<Windows> CreateWindow(const WindowProps& props = WindowProps());
    };
}


