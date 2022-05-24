#include "Render2D.h"
#include"../shader/ShaderPool.h"
namespace CustomSpace
{
    Scope<Render2D::TwoDSceneData> Render2D::m_2DSceneData = CreateScope<Render2D::TwoDSceneData>();
    void Render2D::Init()
    {
    }

    void Render2D::Shutdown()
    {
    }

    void Render2D::BeginScene(const OrthoCamera &camera)
    {
        m_2DSceneData->VPMatrix = camera.GetVPMatrix();
    }

    void Render2D::EndScene()
    {
    }

    void Render2D::RenderTarget(const Ref<Shape> &shape)
    {
        if(m_2DSceneData->m_Shader == nullptr) m_2DSceneData->m_Shader = ShaderPool::Get().getShader(3);
        m_2DSceneData->m_Shader->SetMat4("uVP", m_2DSceneData->VPMatrix);
        m_2DSceneData->m_Shader->SetMat4("uMV", shape->GetTransform()->GetModelMatrix());

        shape->GetVertexData()->m_VAO->Bind();
        if (shape->GetType() == CustomSpace::Shape::ShapeType::Line)
            RenderCommand::RenderLine(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());
        else
            RenderCommand::RenderTarget(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());
    }

    void Render2D::RenderTarget(const Ref<Shader>& shader, const Ref<Shape>& shape)
    {
        m_2DSceneData->m_Shader = shader;
        m_2DSceneData->m_Shader->SetMat4("uVP", m_2DSceneData->VPMatrix);
        m_2DSceneData->m_Shader->SetMat4("uMV", shape->GetTransform()->GetModelMatrix());

        shape->GetVertexData()->m_VAO->Bind();
        if (shape->GetType() == CustomSpace::Shape::ShapeType::Line)
            RenderCommand::RenderLine(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());
        else
            RenderCommand::RenderTarget(shape->GetVertexData()->m_VAO, shape->GetVertexData()->m_VAO->GetEBO()->GetCount());
    }
}