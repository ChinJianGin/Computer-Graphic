#pragma once

#include"./Event.h"

namespace CustomSpace
{
    class KeyEvent : public Event
    {
        public:
            int GetKeyCode() const { return m_KeyCode; }

            EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

        protected:
            KeyEvent(const int keycode) : m_KeyCode(keycode) {}

            int m_KeyCode;
    };

    class KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(const int keycode, const uint16_t repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        uint16_t GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent : " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        uint16_t m_RepeatCount;
    };

    class KeyReleasedEEvent : public KeyEvent
    {
        public:
            KeyReleasedEEvent(const int keycode) : KeyEvent(keycode) {}
            
            std::string ToString() const override
            {
                std::stringstream ss;
                ss << "KeyReleasedEvent : " << m_KeyCode;
                return ss.str();
            }

            EVENT_CLASS_TYPE(KeyReleased);
    };
}