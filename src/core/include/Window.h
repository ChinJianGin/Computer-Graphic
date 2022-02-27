#pragma once

#include "Core.h"

namespace CustomSpace
{
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
}


