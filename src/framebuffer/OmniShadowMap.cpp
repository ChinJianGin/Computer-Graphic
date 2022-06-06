#include"./OmniShadowMap.h"

namespace CustomSpace
{
    OmniShadowMap::OmniShadowMap()
    {

    }

    OmniShadowMap::~OmniShadowMap()
    {
        if(FBO_ID != 0)
        {
            glDeleteFramebuffers(1, &FBO_ID);
        }

        if(MapTexture != 0)
        {
            glDeleteFramebuffers(1, &MapTexture);
        }
    }

    bool OmniShadowMap::Init(const unsigned int width, const unsigned int height)
    {
        m_Width = width;
        m_Height = height;

        glGenFramebuffers(1, &FBO_ID);

        glGenTextures(1, &MapTexture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, MapTexture);
        for(unsigned int i = 0; i < 6; ++i)
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, m_Width, m_Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO_ID);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, MapTexture, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);

        GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

        if(Status != GL_FRAMEBUFFER_COMPLETE)
        {
            CORE_ERROR("Frame buffer error, status : {0}", Status);
            return false;
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // Maybe have problem.
        return true;
    }
    void OmniShadowMap::BindToWrite()
    {
        glViewport(0, 0, m_Width, m_Height);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO_ID);
    }

    void OmniShadowMap::BindToRead(const GLenum unit)
    {
        glActiveTexture(unit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, MapTexture);
    }
}