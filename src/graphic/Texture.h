#pragma once
#include"../core/include/Core.h"

namespace CustomSpace
{
    class Texture
    {
        public:
            virtual ~Texture() = default;

            virtual uint32_t GetWidth()  const = 0;
            virtual uint32_t GetHeight() const = 0;

            virtual void Bind() const = 0;
            virtual void UnBind() const  = 0;
    };

    class Texture2D : public Texture
    {
        public:
            static Ref<Texture2D> Create(const char* path, GLenum texturetype, GLenum slot, GLenum pixeltype);
    };

    class SkyboxTexture : public Texture
    {
        public:
            static Ref<SkyboxTexture> Create(std::vector<std::string> path);
    };
}