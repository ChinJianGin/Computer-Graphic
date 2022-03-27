#include "./RenderCommand.h"

namespace CustomSpace
{
    Scope<RenderInterface> RenderCommand::m_RenderInterface = RenderInterface::Create();
}