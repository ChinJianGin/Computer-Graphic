#include"Renderer.h"
#include"Render2D.h"

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
        if(shader != shape->GetVertexData()->m_Shader)
        {
            shader->Activate();
            shader->SetMat4("uVP", m_SceneData->VPMatrix);
            shader->SetMat4("uMV", shape->GetTransform()->m_ModelMatrix);
        }
        else
        {
            shape->GetVertexData()->m_Shader->Activate();
            shape->GetVertexData()->m_Shader->SetMat4("uVP", m_SceneData->VPMatrix);
            shape->GetVertexData()->m_Shader->SetMat4("uMV",  shape->GetTransform()->m_ModelMatrix);
        }

        shape->GetVertexData()->m_VAO->Bind(); 
        if(shape->GetType() == CustomSpace::Shape::ShapeType::Line)
        RenderCommand::RenderLine(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());
        else
        RenderCommand::RenderTarget(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());  
    }
}