#include"../include/Input.h"
#include"../include/KeyEvent.h"
#include"../include/MouseEvent.h"
namespace CustomSpace
{
    namespace Input
    {
        bool KeyPressedData[GLFW_KEY_LAST] = {};
        bool MouseButtonPressedData[GLFW_MOUSE_BUTTON_LAST] = {};
        float MouseX = 0.0f;
        float MouseY = 0.0f;
        float MouseScrollX = 0.0f;
        float MouseScrollY = 0.0f;

        void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            if(key >= 0 && key < GLFW_KEY_LAST)
            {
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        KeyPressedEvent event(key, 0);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        KeyReleasedEEvent event(key);
                        data.EventCallback(event);
                        break;
                    }
                    case GLFW_REPEAT:
                    {
                        KeyPressedEvent event(key, 1);
                        data.EventCallback(event);
                        break;
                    }
                }
                KeyPressedData[key] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
            }
        }

        void MousePosCallback(GLFWwindow* window, double x_pos, double y_pos)
        {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            MouseMovedEvent event((float)x_pos, (float)y_pos);
            data.EventCallback(event);
            MouseX = (float)x_pos;
            MouseY = (float)y_pos;
        }

        void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
        {
            if(button >= 0 && button < GLFW_MOUSE_BUTTON_LAST)
            {
                WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
                switch (action)
                {
                    case GLFW_PRESS:
                    {
                        MouseButtonPressedData[button] = action;
                        MouseButtonPressedEvent event(button);
                        data.EventCallback(event);       
                        break;
                    }
                    case GLFW_RELEASE:
                    {
                        MouseButtonPressedData[button] = action;
                        MouseButtonReleasedEvent event(button);
                        data.EventCallback(event);
                        break;
                    }
                }
            }
        }

        void MouseScrollCallback(GLFWwindow* window, double x_offset, double y_offset)
        {
            WindowProps& data = *(WindowProps*)glfwGetWindowUserPointer(window);
            MouseScrollEvent event((float)x_offset, (float)y_offset);
            data.EventCallback(event);
            MouseScrollX = (float)x_offset;
            MouseScrollY = (float)y_offset;
        }

        bool IsKeyDown(int key)
        {
            if(key >= 0 && key < GLFW_KEY_LAST)
            {
                return KeyPressedData[key];
            }
            return false;
        }

        bool IsMouseButtonDown(int mouseButton)
        {
            if(mouseButton >= 0 && mouseButton < GLFW_MOUSE_BUTTON_LAST)
            {
                return MouseButtonPressedData[mouseButton];
            }

            return false;
        }
    }
}