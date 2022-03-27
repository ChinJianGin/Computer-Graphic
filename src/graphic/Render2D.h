#pragma once
#include"../core/include/Core.h"
#include"../vertex/VAO.h"
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
    };
}