#pragma once

#include "Core.h"

namespace CustomSpace
{
    namespace Input
    {
        extern bool KeyPressedData[GLFW_KEY_LAST];
        extern bool MouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST];
        extern float MouseX;
        extern float MouseY;
        extern float MouseScrollX;
        extern float MouseScrollY;
        
        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void MousePosCallback(GLFWwindow* window, double x_pos, double y_pos);
        void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void MouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset);

        bool IsKeyDown(int key);
        bool IsMouseButtonDown(int mouseButton);
    }
}