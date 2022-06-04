#pragma once
#include"../core/include/Core.h"

namespace CustomSpace
{
    class ShadowMap
    {
        public:
        ShadowMap();

        ~ShadowMap();

        bool Init(const unsigned int width, const unsigned int height);

        void BindForUpdate();

        void BindForReading(const GLenum textureUnit);

        private:
        uint32_t m_Width = 0;
        uint32_t m_Height = 0;
        GLuint m_FBO;
        GLuint m_ShadowMap;
    };
}