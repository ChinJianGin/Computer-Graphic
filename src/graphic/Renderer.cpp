#include"Renderer.h"
#include"Render2D.h"
#include"RenderCommand.h"
namespace CustomSpace
{
    Scope<Renderer::SceneData> Renderer::m_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init()
    {
        RenderCommand::Init();
        Render2D::Init();
    }

    void Renderer::ShutDown()
    {
        Render2D::Shutdown();
    }

    void Renderer::BeginScene(OrthoCamera& camera)
    {
        m_SceneData->VPMatrix = camera.GetVPMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<Shape>& shape)
    {
        shader->Activate();
        shader->SetMat4("uVP", m_SceneData->VPMatrix);

        
    }
}