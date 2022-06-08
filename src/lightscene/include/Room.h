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
#include"../../graphic/Skybox.h"

constexpr int SPOTLIGHTNUM = 3;
constexpr int FLOORNUM = 6;
constexpr int CEILINGNUM = 6;
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
        CustomSpace::Ref<CustomSpace::Shape> m_Box;
        CustomSpace::Ref<CustomSpace::Shape> m_Pyramid;
        CustomSpace::Ref<CustomSpace::Shape> m_Wall[10], m_Ground[FLOORNUM], m_Ceiling[CEILINGNUM], m_InnerWall[4], m_Middle_Wall[2], m_WoodDoor[2];
        CustomSpace::Ref<CustomSpace::Light> m_DirLight, m_PointLight, m_SpotLight[SPOTLIGHTNUM];

        CustomSpace::Ref<CustomSpace::Texture2D> m_StoneTex, m_StoneSpec, m_WoodTex, m_WoodSpec, m_FriendCubeTex, m_FriendCubeSpec;
        CustomSpace::Ref<CustomSpace::Texture2D> m_hl2_ceiling, m_hl2_wall[2], m_hl2_wall_normal[2], m_hl2_wall_middle, m_hl2_wall_middle_normal;
        CustomSpace::Ref<CustomSpace::Texture2D> m_hl2_tile, m_hl2_tile_spec, m_hl2_floor_normal, m_hl2_wood_door, m_hl2_wood_door_normal;

        CustomSpace::Ref<CustomSpace::Texture2D> m_pt2_ceiling, m_pt2_ceiling_normal, m_pt2_wall[2], m_pt2_wall_normal, m_pt2_wall_spec;
        CustomSpace::Ref<CustomSpace::Texture2D> m_pt2_tile, m_pt2_tile_spec, m_pt2_floor_normal;

        CustomSpace::Ref<CustomSpace::ShadowMap> m_ShadowMap;
        CustomSpace::Ref<CustomSpace::OmniShadowMap> m_OmniShadowMap;

        CustomSpace::Ref<CustomSpace::Skybox> m_Skybox;

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

        float m_AllTime = 0;

        void Init();

        void ObjectInit();

        void ModelInit();

        void ShaderInit();

        void TextureInit();

        void LightInit();
        void LightControl();

        void RoomInit();
        void RoomUpdate();

        void RGBControl(const glm::vec3& value);

        void RoomReset();

        void RenderQuad();
        void RenderNormalScene();
        void RenderShadowScene();

        int framebuffer_width = 0, framebuffer_height = 0;

        void ShadowMapUpdate();
        void OmniShadowMapUpdate();

        // Model
        CustomSpace::Ref<CustomSpace::Model> m_HeadCrab, m_Crowbar, m_PortalGun;
};