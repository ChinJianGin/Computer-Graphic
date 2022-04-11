#pragma once

#include"../../core/include/Core.h"
#include"../../graphic/Renderer.h"
#include"../../client/include/Creator.h"
#include"../../graphic/Texture.h"

class ShootingGame
{
public:
    ShootingGame(int width = 512, int height = 512, const char* title = "", bool screenmode = false, bool vsync = false);

    void Run();

    void Close();
private:
    //CustomSpace::Ref<VAO> TriangleVAO;
    //CustomSpace::Ref<Shader> TriangleShaderProgram;

    CustomSpace::Ref<CustomSpace::OrthoCamera> m_Camera;

    CustomSpace::Scope<CoreTimer> m_Timer;
private:
    static ShootingGame* Instance;
    CustomSpace::Scope<CustomSpace::Windows> M_Window;
    bool B_Running = true;

    CustomSpace::Ref<CustomSpace::Shape> m_Triangle;
    CustomSpace::Ref<CustomSpace::Shape> m_Triangle_2;
    CustomSpace::Ref<CustomSpace::Shape> m_Quad;
    CustomSpace::Ref<CustomSpace::Texture2D> m_Texture;
    CustomSpace::Ref<CustomSpace::Texture2D> m_Texture2;

    CustomSpace::Ref<CustomSpace::ShapeFactory> m_Factory;
    glm::vec3 CameraPosition;
    glm::vec3 Transform;
    glm::vec3 Transform2;

    float m_Rotation = 0.f;
    float m_RotationSpeed = 1.f;    
    float m_MoveSpeed = 1.f;
    float m_Scale = 1;
};