#include"Renderer.h"

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
        Render2D::BeginScene(camera);
    }

    void Renderer::BeginScene(PerspectiveCamera& camera)
    {
        m_SceneData->VPMatrix = camera.GetVPMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const Ref<Shader>& shader, const Ref<Shape>& shape)
    {
        shader->SetMat4("uVP", m_SceneData->VPMatrix);
        shader->SetMat4("uMV", shape->GetTransform()->GetModelMatrix());

        shape->GetVertexData()->m_VAO->Bind(); 
        if(shape->GetType() == CustomSpace::Shape::ShapeType::Line)
        RenderCommand::RenderLine(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());
        else
        RenderCommand::RenderTarget(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());  
    }
}