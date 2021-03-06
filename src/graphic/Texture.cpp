#include"./Texture.h"
#include"./OpenGLTexture.h"
namespace CustomSpace
{
    Ref<Texture2D> Texture2D::Create(const char* path, GLenum texturetype, GLenum slot, GLenum pixeltype)
    {
        return CreateRef<OpenGLTexture2D>(path, texturetype, slot, pixeltype);
    }

    Ref<SkyboxTexture> SkyboxTexture::Create(std::vector<std::string> path)
    {
        return CreateRef<OpenGLCubeTexture>(path);
    }
}