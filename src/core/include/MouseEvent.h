#pragma once
#include"./Event.h"

namespace CustomSpace
{
    class MouseMovedEvent : public Event
    {
        public:

            MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

            float GetX() const { return m_MouseX; }
            float GetY() const { return m_MouseY; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseMoved);
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        private:
        float m_MouseX , m_MouseY;
    };

    class MouseScrollEvent : public Event
    {
        public:
            MouseScrollEvent(const float x_offset, const float y_offset) : m_XOffset(x_offset), m_YOffset(y_offset) {}

            float GetXOffset() const { return m_XOffset; }
            float GetYOffset() const { return m_YOffset; }

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseScrollEvent: " << m_XOffset << ", " << m_YOffset;
                return ss.str();
            }

            EVENT_CLASS_TYPE(MouseScrolled);
            EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse)

        private:
            float m_XOffset, m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
        public:
            GLint GetMouseButton() const { return m_Button; }
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
        
        protected:
            MouseButtonEvent(const GLint button) : m_Button(button) {}

            GLint m_Button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonPressedEvent(const GLint button) : MouseButtonEvent(button) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonPressedEvent: " << m_Button;
                return ss.str();
            }
            EVENT_CLASS_TYPE(MouseButtonPressed);
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
        public:
            MouseButtonReleasedEvent(const GLint button) : MouseButtonEvent(button) {}

            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "MouseButtonReleasedEvent: " << m_Button;
                return ss.str();
            }
            
            EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}