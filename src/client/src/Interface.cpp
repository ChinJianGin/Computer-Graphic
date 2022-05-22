#include "../include/Interface.h"
#include "../../lightscene/include/3DScene.h"

namespace CustomSpace
{
    UserInterface::UserInterface()
    {
        this->Init();
    }

    void UserInterface::Init()
    {
        float _x = 1.5f, _y = .8f, _z = 0.f;
        float _xscale = .35f, _yscale = .2f;
        Ref<Button> button = CreateRef<Button>();
        button->SetPosition(glm::vec3(_x, _y, _z));
        button->SetScale(glm::vec3(_xscale, _yscale, 1.f));
        glm::mat4 _MM = button->GetBody()->GetTransform()->GetTranslate() * button->GetBody()->GetTransform()->GetScale();
        button->SetModelMatrix(_MM);
        m_Buttons.push_back(button);

        button = CreateRef<Button>();
        button->SetPosition(glm::vec3(-_x, _y, _z));
        button->SetScale(glm::vec3(_xscale, _yscale, 1.f));
        _MM = button->GetBody()->GetTransform()->GetTranslate() * button->GetBody()->GetTransform()->GetScale();
        button->SetModelMatrix(_MM);
        m_Buttons.push_back(button);

        button = CreateRef<Button>();
        button->SetPosition(glm::vec3(-_x, -_y, _z));
        button->SetScale(glm::vec3(_xscale, _yscale, 1.f));
        _MM = button->GetBody()->GetTransform()->GetTranslate() * button->GetBody()->GetTransform()->GetScale();
        button->SetModelMatrix(_MM);
        m_Buttons.push_back(button);

        button = CreateRef<Button>();
        button->SetPosition(glm::vec3(_x, -_y, _z));
        button->SetScale(glm::vec3(_xscale, _yscale, 1.f));
        _MM = button->GetBody()->GetTransform()->GetTranslate() * button->GetBody()->GetTransform()->GetScale();
        button->SetModelMatrix(_MM);
        m_Buttons.push_back(button);

        glfwGetWindowSize((GLFWwindow*)LightTestRoom::Get().GetWindow().GetWindow(), &m_Width, &m_Height);
        m_Aspecratio = (float)m_Width / m_Height;
    }

    void UserInterface::OnUpdate(CoreTimer &timer)
    {
        for (int i = 0; i < m_Buttons.size(); i++)
        {
            Render2D::RenderTarget(m_Buttons[i]->GetBody()->GetVertexData()->m_Shader, m_Buttons[i]->GetBody());
            m_Buttons[i]->GetBody()->GetVertexData()->m_Shader->SetInt("HaveTex", 0);
        }
    }

    void UserInterface::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT(UserInterface::OnMouseInput));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(UserInterface::OnMouseMoved));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(UserInterface::OnWindowResized));
    }

    bool UserInterface::OnMouseInput(MouseButtonPressedEvent &event)
    {
        if (glfwGetInputMode((GLFWwindow *)LightTestRoom::Get().GetWindow().GetWindow(), GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
        {
            float normal_x = m_Aspecratio * (2.f * (float)m_MouseX / m_Width - 1.f) , normal_y = 2.f * (float)(m_Height - m_MouseY) / m_Height - 1.f;
            CORE_INFO("Normal mouse X : {0} , Y : {1}", normal_x, normal_y);
            this->Clicked(glm::vec2(normal_x, normal_y));
        }
        return false;
    }

    bool UserInterface::OnMouseMoved(MouseMovedEvent &event)
    {
        if (glfwGetInputMode((GLFWwindow *)LightTestRoom::Get().GetWindow().GetWindow(), GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
        {
            m_MouseX = event.GetX();
            m_MouseY = event.GetY();
        }
        return false;
    }

    bool UserInterface::OnWindowResized(WindowResizeEvent &event)
    {
        for(int i = 0; i < m_Buttons.size(); i++)
            CORE_TRACE("Button {0} world pos X : {1} , Y : {2}", i, m_Buttons[i]->GetBody()->GetTransform()->GetWorldPosition().x, m_Buttons[i]->GetBody()->GetTransform()->GetWorldPosition().y);
        return false;
    }

    void UserInterface::Clicked(const glm::vec2 &cpos)
    {
        for (int i = 0; i < m_Buttons.size(); i++)
        {
            if (m_Buttons[i]->OnClicked(cpos))
            {
                break;
            }
        }
    }
}