#include"./ShadowMapFBO.h"

namespace CustomSpace
{
    ShadowMap::ShadowMap()
    {
    }

    ShadowMap::~ShadowMap()
    {
        if(m_FBO != 0)
            glDeleteFramebuffers(1, &m_FBO);

        if(m_ShadowMap != 0)
            glDeleteFramebuffers(1, &m_ShadowMap);
    }

    bool ShadowMap::Init(const unsigned int width, const unsigned int height)
    {
        m_Width = width;
        m_Height = height;

        glGenFramebuffers(1, &m_FBO);

        glGenTextures(1, &m_ShadowMap);
        glBindTexture(GL_TEXTURE_2D, m_ShadowMap);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

        float clampColor[] = { 1.f, 1.f, 1.f, 1.f };
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);

        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_ShadowMap, 0);

        // Disable writes to the color buffer
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if(Status != GL_FRAMEBUFFER_COMPLETE)
        {
            CORE_ERROR("Frame buffer error, status : {0}", Status);
            return false;
        }

        // glBindFramebuffer(GL_FRAMEBUFFER, 0); // I don't know why wrtie this here will get wrong result.

        return true;
    }

    void ShadowMap::BindForUpdate()
    {
        glViewport(0, 0, m_Width, m_Height);
        glBindBuffer(GL_DRAW_FRAMEBUFFER, m_FBO);
    }

    void ShadowMap::BindForReading(const GLenum textureUnit)
    {
        glActiveTexture(textureUnit);
        glBindTexture(GL_TEXTURE_2D, m_ShadowMap);
    }
}