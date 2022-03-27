#include"RenderInterface.h"
#include"OpenGLRenderCommand.h"

namespace CustomSpace
{
    Scope<RenderInterface> RenderInterface::Create()
    {
        return CreateScope<OpenGLRenderCommand>();
    }
}