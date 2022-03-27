#include"./OpenGLRenderCommand.h"

namespace CustomSpace
{
    void OpenGLRenderCommand::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }
            
    void OpenGLRenderCommand::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(x, y, width, height);
    }
    void OpenGLRenderCommand::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
            
    void OpenGLRenderCommand::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

           
    void OpenGLRenderCommand::DrawElement(const Ref<VAO>& vao, uint32_t count)
    {
        uint32_t IndexCount = (count ? count : vao->GetEBO()->GetCount()) / sizeof(GLuint);
        glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, nullptr);
    }
}