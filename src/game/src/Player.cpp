#include"../include/Player.h"


namespace CustomSpace
{
    APlayer::APlayer(const Ref<ShapeFactory>& factory)
    {
        this->Init(factory);
    }

    void APlayer::Init(const Ref<ShapeFactory>& factory)
    {
        m_Body = factory->ShapeCreator<Quad>();
        if(m_Body == nullptr)
        {
            CORE_ERROR("Player body not set.");
            return;
        }
        m_Body->GetBounding()->SetNeedTest(true);
    }

    void APlayer::Update(const CoreTimer& timer)
    {
        Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
    }

    void APlayer::SetTransform(const Ref<Transform>& trans)
    {
        this->m_Body->SetTransform(trans);
    }

    void APlayer::SetPosition(const glm::vec3& pos)
    {
        this->m_Body->SetPosition(pos);
    }

    void APlayer::SetPosition(const float pos, int axis)
    {
        this->m_Body->SetPosition(pos, axis);
    }

    void APlayer::SetColor(const std::vector<glm::vec4> colors)
    {
        this->m_Body->SetColor(colors);
    }

    void APlayer::SetRotation(const float rotation, const glm::vec3& axis)
    {
        this->m_Body->SetRotation(rotation, axis);
    }

    void APlayer::SetScale(const glm::vec3& scale)
    {
        this->m_Body->SetScale(scale);
    }

    void APlayer::ModelMatrixMethod(Shape::MatrixMethod method)
    {
        this->ModelMatrixMethod(method);
    }

    void APlayer::AttackAction()
    {

    }
}