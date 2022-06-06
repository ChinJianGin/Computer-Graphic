#pragma once
#include"../core/include/Core.h"
#include"./Texture.h"

namespace CustomSpace
{
    class Skybox
    {
        public:
            Skybox();
            ~Skybox();

            void Init();

            void Draw();

        private:
            unsigned int m_VAO, m_VBO, m_EBO;
            Ref<SkyboxTexture> m_Texture;
    };
}