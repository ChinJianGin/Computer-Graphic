#pragma once

#include"../../core/include/Core.h"
#include"../../graphic/Renderer.h"
#include"../../graphic/Texture.h"
#include"../../client/include/Creator.h"
#include"../../core/include/Event.h"
#include"../../core/include/KeyEvent.h"
#include"../../core/include/WindowEvent.h"
#include"../../core/include/PerspectiveCameraController.h"
#include"../../graphic/ModelLoad/Model.h"

class LightTestRoom
{
    public:
        LightTestRoom(int width = 512, int height = 512, const char* title = "", bool screenmode = false, bool vsync = false);

        ~LightTestRoom();
        void Run();

        void OnEvent(CustomSpace::Event& e);
        bool OnKeyPressedEvent(CustomSpace::KeyPressedEvent& event);
        bool OnWindowResizeEvent(CustomSpace::WindowResizeEvent& event);

        void Close();


        static LightTestRoom& Get() { return * Instance; }
        CustomSpace::Windows& GetWindow() { return *m_Window; }

    private:
        CustomSpace::Ref<CustomSpace::OrthoCamera> m_OrthoCamera;
        CustomSpace::Ref<CustomSpace::PerspectiveCameraController> m_PersController;

        CustomSpace::Scope<CustomSpace::ShapeFactory> m_Factory;
        CustomSpace::Ref<CustomSpace::Shape> m_Triangle;
        CustomSpace::Ref<CustomSpace::Shape> m_Pyramid;

        CustomSpace::Ref<CustomSpace::Texture2D> m_StoneTex;

        CustomSpace::Scope<CoreTimer> m_Timer;

        static LightTestRoom* Instance;
        CustomSpace::Scope<CustomSpace::Windows> m_Window;

        bool b_Running = true;

        glm::vec3 m_CamPosition;


        // Model test
        CustomSpace::Ref<Shader> m_ModelShader;
        CustomSpace::Ref<CustomSpace::Model> m_HeadCrab;
};