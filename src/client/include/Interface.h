#pragma once
#include "../../core/include/Core.h"
#include "./Button.h"
#include "../../core/include/Event.h"
#include "../../core/include/MouseEvent.h"
#include "../../core/include/WindowEvent.h"

namespace CustomSpace
{
    class UserInterface
    {
    public:
        UserInterface();
        ~UserInterface() = default;

        void Init();

        void OnUpdate(CoreTimer &timer);
        void OnEvent(Event &event);

        bool OnMouseInput(MouseButtonPressedEvent& event);
        bool OnMouseReleased(MouseButtonReleasedEvent& event);
        bool OnMouseMoved(MouseMovedEvent& event);
        bool OnWindowResized(WindowResizeEvent& event);

        const bool* IsButtonActive() { return this->b_ButtonIsActive; }

        void Clicked(const glm::vec2& cpos);

        const bool IsFocusOnInterface() const { return b_FocusInterface; }
        void UnFocus() { b_FocusInterface = false; }

        const int LastChooseButton() { return this->m_LastChoose; }

        void Reset();
    private:
        std::vector<Ref<Button>> m_Buttons;

        int m_Width, m_Height;
        float m_Aspecratio, m_MouseX, m_MouseY;

        bool b_FocusInterface = false;
        bool b_ButtonIsActive[4] = {false};

        int m_LastChoose = 0;

        std::vector<glm::vec4> m_ButtonColors; 
    };
}