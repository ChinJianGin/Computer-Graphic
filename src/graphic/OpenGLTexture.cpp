#include"./OpenGLTexture.h"
#define STB_IMAGE_IMPLEMENTATION
#include"../core/include/stb_image.h"
namespace CustomSpace
{
    OpenGLTexture2D::OpenGLTexture2D(const char* path, GLenum type, GLenum slot, GLenum pixeltype) : m_Path(path), m_Type(type), m_Slot(slot)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        stbi_uc* data = stbi_load(path, &width, &height, &channels, 0);
        m_Width = width;
        m_Height = height;
        GLenum m_Format;
        switch(channels)
        {
            case 0:
                CORE_ERROR("Image doesn't have any channels");
                break;
            case 1:
                m_Format = GL_R;
                break;
            case 2:
                m_Format = GL_RG;
                break;
            case 3:
                m_Format = GL_RGB;
                break;
            case 4:
                m_Format = GL_RGBA;
                break;

            default:
                m_Format = GL_RGB;
        }

        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_2D, ID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        if(data)
        {
            CORE_WARN("Width : {0}, Height : {1}, Channels : {2}", m_Width, m_Height, channels);
            glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, m_Format, m_Width, m_Height, 0, m_Format, pixeltype, data);
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

    OpenGLCubeTexture::OpenGLCubeTexture(std::vector<std::string> path)
    {
        glGenTextures(1, &ID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        int width, height, channels;
        unsigned char *data;
        stbi_set_flip_vertically_on_load(false);
        for(unsigned int i = 0; i < path.size(); i++)
        {
            data = stbi_load(path[i].c_str(), &width, &height, &channels, 0);
            m_Width = width;
            m_Height = height;
            GLenum m_Format;
            switch(channels)
            {
                case 0:
                    CORE_ERROR("Image doesn't have any channels");
                    break;
                case 1:
                    m_Format = GL_R;
                    break;
                case 2:
                    m_Format = GL_RG;
                    break;
                case 3:
                    m_Format = GL_RGB;
                    break;
                case 4:
                    m_Format = GL_RGBA;
                    break;

                default:
                    m_Format = GL_RGB;
            }
            if(data)
            {
                CORE_WARN("Width : {0}, Height : {1}, Channels : {2}", m_Width, m_Height, channels);
                glTexImage2D(
                    GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0,
                    m_Format,
                    width,
                    height,
                    0,
                    m_Format,
                    GL_UNSIGNED_BYTE,
                    data
                );
                stbi_image_free(data);
            }
            else
            {
                CORE_ERROR("Failed to load texture face : {0}", i);
                stbi_image_free(data);
            }
        }
    }

    OpenGLCubeTexture::~OpenGLCubeTexture()
    {
        glDeleteTextures(1, &ID);
    }

    void OpenGLCubeTexture::Bind() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
    }

    void OpenGLCubeTexture::UnBind() const
    {

    }
}