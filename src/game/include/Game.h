#pragma once

#include"./Scene.h"
#include"../../core/include/Event.h"
#include"../../core/include/KeyEvent.h"

class ShootingGame
{
public:
    ShootingGame(int width = 512, int height = 512, const char* title = "", bool screenmode = false, bool vsync = false);

    void Run();

    void OnEvent(CustomSpace::Event& e);
    bool OnKeyPressedEvent(CustomSpace::KeyPressedEvent& event);

    void Close();

    static ShootingGame& Get() { return *Instance; }
    CustomSpace::Windows& GetWindow() { return *M_Window; }
private:
    CustomSpace::Ref<CustomSpace::OrthoCamera> m_Camera;

    CustomSpace::Scope<CoreTimer> m_Timer;
private:
    static ShootingGame* Instance;
    CustomSpace::Scope<CustomSpace::Windows> M_Window;
    bool B_Running = true;

    CustomSpace::Ref<CustomSpace::Scene> m_Scene1;
    
    CustomSpace::Ref<CustomSpace::ShapeFactory> m_Factory;
    glm::vec3 m_CameraPosition;
    glm::vec3 m_Transform;
    glm::vec3 m_Transform2;

    CustomSpace::Ref<CustomSpace::Transform> OriginTrans;

    float m_Rotation = 0.f;
    float m_RotationSpeed = 1.f;    
    float m_MoveSpeed = 1.f;
    glm::vec3 m_Scale = glm::vec3(1);
    int Test = 0;
};