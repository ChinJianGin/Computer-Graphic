#pragma once
#include"../core/include/Core.h"
#include"../vertex/VAO.h"
#include"./RenderCommand.h"
#include"./Shape.h"

namespace CustomSpace
{
    class Render2D
    {
        public:
            static void Init();

            static void Shutdown();

            static void BeginScene(const OrthoCamera& camera);
            static void EndScene();

            static void RenderTarget(const Ref<Shape>& shape);
            static void RenderTarget(const Ref<Shader>& shader, const Ref<Shape>& shape);

        private:
            struct TwoDSceneData
            {
                Ref<Shader> m_Shader;
                glm::mat4 VPMatrix;
            };

            static Scope<TwoDSceneData> m_2DSceneData;
    };
}