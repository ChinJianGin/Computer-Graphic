#pragma once

#include"../../core/include/Core.h"
#include"../../graphic/Renderer.h"

class LightTestRoom
{
    public:
        LightTestRoom(int width = 512, int height = 512, const char* title = "", bool screenmode = false, bool vsync = false);

        void Run();


        void Close();


        static LightTestRoom& Get() { return * Instance; }
        CustomSpace::Windows& GetWindow() { return *m_Window; }

    private:
        CustomSpace::Ref<CustomSpace::OrthoCamera> m_Camera;

        CustomSpace::Scope<CoreTimer> m_Timer;

        static LightTestRoom* Instance;
        CustomSpace::Scope<CustomSpace::Windows> m_Window;

        bool b_Running = true;
};