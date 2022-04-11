#include"./OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../core/include/stb_image.h"
namespace CustomSpace
{
    OpenGLTexture2D::OpenGLTexture2D(const char* path, GLenum type, GLenum slot, GLenum format, GLenum pixeltype) : m_Path(path), m_Type(type), m_Slot(slot)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
        m_Width = width;
        m_Height = height;

        glGenTextures(1, &ID);
        glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, pixeltype, data);
            glGenerateMipmap(m_Type);
        }
        else
        {
            CORE_ERROR("Failed to load texture");
        }
        stbi_image_free(data);
        this->UnBind();
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &ID);
    }

    void OpenGLTexture2D::Bind() const
    {
        glActiveTexture(m_Slot);
        glBindTexture(m_Type, ID);
    }

    void OpenGLTexture2D::UnBind() const
    {
        glBindTexture(m_Type, 0);
    }
}