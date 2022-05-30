#include "../include/Interface.h"
#include "../../lightscene/include/3DScene.h"
#include "../../shader/ShaderPool.h"

namespace CustomSpace
{
    UserInterface::UserInterface()
    {
        this->Init();
    }

    void UserInterface::Init()
    {
        m_ButtonColors = 
        {
            glm::vec4(.94f, .92f, .78f, 1.f),
            glm::vec4(0.f, 1.f, 0.f, 1.f),
            glm::vec4(1.f, 0.f, 0.f, 1.f),
            glm::vec4(0.f, 0.f, 1.f, 1.f)
        };
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
            ShaderPool::Get().getShader(3)->Activate();
            ShaderPool::Get().getShader(3)->SetInt("HaveTex", false);
            if(!b_ButtonIsActive[i])
                ShaderPool::Get().getShader(3)->SetFloat4("uColor", m_ButtonColors[i]);
            else
                ShaderPool::Get().getShader(3)->SetFloat4("uColor", glm::vec4(.1f, .1f, .1f, 1.f));
            Render2D::RenderTarget(ShaderPool::Get().getShader(3), m_Buttons[i]->GetBody());
        }
    }

    void UserInterface::OnEvent(Event &event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT(UserInterface::OnMouseInput));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT(UserInterface::OnMouseReleased));
        dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT(UserInterface::OnMouseMoved));
        dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT(UserInterface::OnWindowResized));
    }

    bool UserInterface::OnMouseInput(MouseButtonPressedEvent &event)
    {
        if (glfwGetInputMode((GLFWwindow *)LightTestRoom::Get().GetWindow().GetWindow(), GLFW_CURSOR) != GLFW_CURSOR_DISABLED && event.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
        {
            float normal_x = m_Aspecratio * (2.f * (float)m_MouseX / m_Width - 1.f) , normal_y = 2.f * (float)(m_Height - m_MouseY) / m_Height - 1.f;
            this->Clicked(glm::vec2(normal_x, normal_y));
        }
        return false;
    }

    bool UserInterface::OnMouseReleased(MouseButtonReleasedEvent& event)
    {
        if(event.GetMouseButton() == GLFW_MOUSE_BUTTON_LEFT)
        {
            this->UnFocus();
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
        if(event.GetWidth() == 0 || event.GetHeight() == 0)
        {
            return false;
        }
        m_Width = event.GetWidth();
        m_Height = event.GetHeight();
        m_Aspecratio = (float)m_Width / m_Height;
        return false;
    }

    void UserInterface::Clicked(const glm::vec2 &cpos)
    {
        for (int i = 0; i < m_Buttons.size(); i++)
        {
            if (m_Buttons[i]->OnClicked(cpos))
            {
                GAME_INFO("Button num : {0}", i);
                b_ButtonIsActive[i] = !b_ButtonIsActive[i];
                m_LastChoose = i;
                b_FocusInterface = true;
                break;
            }
        }
    }

    void UserInterface::Reset()
    {
        b_FocusInterface = false;
        for(int i = 0; i < 4; i++)
        {
            b_ButtonIsActive[i] = false;
        }
        m_LastChoose = 0;
    }
}