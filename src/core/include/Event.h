#pragma once

#include"./Core.h"

namespace CustomSpace
{
    enum class EventType
    {
        None = 0,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryInput = BIT(0),
        EventCategoryKeyboard = BIT(1),
        EventCategoryMouse = BIT(2),
        EventCategoryMouseButton = BIT(3)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; } \
                               virtual EventType GetEventType() const override { return GetStaticType(); } \
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


    class Event
    {
        public:
            virtual ~Event() = default;

            bool IsHandled = false;

            virtual EventType GetEventType() const = 0;
            virtual const char* GetName() const = 0;
            virtual int GetCategoryFlags() const = 0;
            virtual std::string ToString() const { return GetName(); }

            bool IsInCategory(EventCategory category)
            {
                return GetCategoryFlags() & category;
            }
    };

    class EventDispatcher
    {
        public:
            EventDispatcher(Event& event) : m_Event(event)
            {
            }

            template<typename T, typename F>
            bool Dispatch(const F& func)
            {
                if(m_Event.GetEventType() == T::GetStaticType())
                {
                    m_Event.IsHandled |= func(static_cast<T&>(m_Event));
                    return true;
                }
                return false;
            }
        private:
            Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}