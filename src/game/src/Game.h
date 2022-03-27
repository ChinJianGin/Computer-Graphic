#pragma once

#include"../../core/include/Core.h"
#include"../../vertex/VAO.h"

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

    //CustomSpace::Ref<CustomSpace::Triangle> m_Triangle;

    glm::vec3 CameraPosition;

    float CameraRotation = 0.f;
    float CameraRotationSpeed = 10.f;    
    float CameraMoveSpeed = 1.f;
};