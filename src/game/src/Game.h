#pragma once

#include"../../core/include/Core.h"
#include"../../vertex/VAO.h"
#include"../../graphic/Renderer.h"

class ShootingGame
{
public:
    ShootingGame(int width = 512, int height = 512, const char* title = "", bool screenmode = false, bool vsync = false);

    void Run();

    void Close();
private:
    CustomSpace::Ref<VAO> TriangleVAO;
    CustomSpace::Ref<Shader> TriangleShaderProgram;

    CustomSpace::Ref<CustomSpace::OrthoCamera> m_Camera;

    CustomSpace::Scope<CoreTimer> m_Timer;
private:
    static ShootingGame* Instance;
    CustomSpace::Scope<CustomSpace::Windows> M_Window;
    bool B_Running = true;

    CustomSpace::Ref<CustomSpace::Triangle> m_Triangle;

    glm::vec3 CameraPosition;
    glm::vec3 Transform;

    float m_Rotation = 0.f;
    float m_RotationSpeed = 1.f;    
    float m_MoveSpeed = 1.f;
    float m_Scale = 1;
};