#pragma once
#include "../core/include/OrthoCamera.h"
#include "../core/include/PerspectiveCamera.h"
#include "../shader/ShaderClass.h"
#include"RenderCommand.h"
#include "./OpenGLRenderCommand.h"
#include"Render2D.h"
#include "Shape.h"
#include "Triangle.h"
#include "Quad.h"
#include "Line.h"
#include "Circle.h"
#include "3DModel.h"
#include "Pyramid.h"
#include "Plane.h"
#include "Box.h"

namespace CustomSpace
{
    class Renderer
    {
        public:
            static void Init();
            static void ShutDown();

            static void BeginScene(OrthoCamera& camera);
            static void BeginScene(PerspectiveCamera& camera);
            static void EndScene();

            static void Submit(const Ref<Shader>& shader, const Ref<Shape>& shape);
            static void SubmitShadow(const Ref<Shader>& shader, const Ref<Shape>& shape);

        private:
            struct SceneData
            {
                glm::mat4 VPMatrix;
            };

            static Scope<SceneData> m_SceneData;
    };
}