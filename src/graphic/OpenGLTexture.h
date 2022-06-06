#pragma once

#include"./Texture.h"

namespace CustomSpace
{
    class OpenGLTexture2D : public Texture2D
    {
        public:
            OpenGLTexture2D(const char* path, GLenum texturetype, GLenum slot, GLenum pixeltype);
            virtual ~OpenGLTexture2D();
            virtual uint32_t GetWidth() const override {return m_Width;};
            virtual uint32_t GetHeight() const override {return m_Height;};

            virtual void Bind() const override;
            virtual void UnBind() const override; 
        private:
            const char* m_Path;
            uint32_t m_Width, m_Height;
            uint32_t ID;
            GLenum m_Type, m_Slot;
    };

    class OpenGLCubeTexture : public SkyboxTexture
    {
        public:
            OpenGLCubeTexture(std::vector<std::string> path);
            virtual ~OpenGLCubeTexture();
            virtual uint32_t GetWidth() const override {return m_Width;};
            virtual uint32_t GetHeight() const override {return m_Height;};

            virtual void Bind() const override;
            virtual void UnBind() const override; 
        private:
            std::vector<std::string> m_Path;
            uint32_t m_Width, m_Height;
            uint32_t ID;
    };
}