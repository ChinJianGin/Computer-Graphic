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
#include"../../client/include/Interface.h"
#include"../../shader/ShaderPool.h"
#include"../../light/Light.h"
#include"../../framebuffer/ShadowMapFBO.h"
#include"../../framebuffer/OmniShadowMap.h"

constexpr int SPOTLIGHTNUM = 3;
constexpr int FLOORNUM = 6;
const unsigned int SHADOW_MAP_WIDTH = 2048;
const unsigned int SHADOW_MAP_HEIGHT = 2048;

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
        CustomSpace::Ref<CustomSpace::Shape> m_Box, m_Ground[FLOORNUM], m_Ceiling;
        CustomSpace::Ref<CustomSpace::Shape> m_Wall[4];
        CustomSpace::Ref<CustomSpace::Shape> m_Pyramid;
        CustomSpace::Ref<CustomSpace::Light> m_DirLight, m_PointLight, m_SpotLight[SPOTLIGHTNUM];

        CustomSpace::Ref<CustomSpace::Texture2D> m_StoneTex, m_StoneSpec, m_WoodTex, m_WoodSpec, m_FriendCubeTex, m_FriendCubeSpec, m_MetalFloorTex, m_MetalFloorSpec;
        CustomSpace::Ref<CustomSpace::Texture2D> m_CeilingTex, m_WallTex[2];
        CustomSpace::Ref<CustomSpace::Texture2D> m_FloorNomrmal;
        CustomSpace::Ref<CustomSpace::Texture2D> m_hl2_tile, m_hl2_tile_spec, m_hl2_floor_normal;

        CustomSpace::Ref<CustomSpace::ShadowMap> m_ShadowMap;
        CustomSpace::Ref<CustomSpace::OmniShadowMap> m_OmniShadowMap;

        CustomSpace::Scope<CoreTimer> m_Timer;

        CustomSpace::Scope<CustomSpace::UserInterface> m_Interface;

        CustomSpace::Scope<ShaderPool> m_ShaderPool;

        std::vector<CustomSpace::Ref<CustomSpace::Shape>> m_MeshContainer;

        static LightTestRoom* Instance;
        CustomSpace::Scope<CustomSpace::Windows> m_Window;

        bool b_Running = true;

        glm::vec3 m_CamPosition;

        glm::vec3 m_OriginAmbient[4], m_PointLightPos;

        glm::mat4 m_LightProjection = glm::mat4(1.f);

        void LightControl();

        float m_AllTime = 0;

        void RoomInit();
        void RoomUpdate();

        void RGBControl(const glm::vec3& value);

        void RoomReset();

        void RenderQuad();

        int framebuffer_width = 0, framebuffer_height = 0;

        void ShadowMapUpdate();

        // Model test
        CustomSpace::Ref<CustomSpace::Model> m_HeadCrab, m_Crowbar, m_PortalGun;
};