#pragma once

#include"../core/include/Core.h"

namespace CustomSpace
{
    class OmniShadowMap
    {
        public:
            OmniShadowMap();
            ~OmniShadowMap();

            bool Init(const unsigned int width, const unsigned int height);

            void BindToWrite();

            void BindToRead(const GLenum unit);
        private:
        unsigned int m_Width, m_Height;
        GLuint FBO_ID;
        GLuint MapTexture;
    };
}