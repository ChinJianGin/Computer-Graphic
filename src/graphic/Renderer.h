#pragma once
#include "../core/include/OrthoCamera.h"
#include "../shader/ShaderClass.h"
#include "./OpenGLRenderCommand.h"
#include "Shape.h"
#include "Triangle.h"

namespace CustomSpace
{
    class Renderer
    {
        public:
            static void Init();
            static void ShutDown();

            static void BeginScene(OrthoCamera& camera);
            static void EndScene();

            static void Submit(const Ref<Shader>& shader, const Ref<Shape>& shape);

        private:
            struct SceneData
            {
                glm::mat4 VPMatrix;
            };

            static Scope<SceneData> m_SceneData;
    };
}