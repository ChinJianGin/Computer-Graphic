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
        m_Shield = factory->ShapeCreator<Circle>();
        m_Shield->SetScale(glm::vec3(1.25, 1.25, 0));
        if(m_Body == nullptr)
        {
            CORE_ERROR("Player body not set.");
            return;
        }
        m_Body->GetBounding()->SetNeedTest(true);
        m_BoundingVolume = m_Body;
        m_PlayerTex = Texture2D::Create("../src/TextureSrc/PlayerShip.png", GL_TEXTURE_2D, GL_TEXTURE2, GL_UNSIGNED_BYTE);
    }

    void APlayer::Update(const CoreTimer& timer)
    {
        m_PlayerTex->Bind();
        Renderer::Submit(m_Body->GetVertexData()->m_Shader, m_Body);
        m_Body->GetVertexData()->m_Shader->SetInt("tex0", 2);
        m_PlayerTex->UnBind();

        m_Shield->SetPosition(m_Body->GetTransform()->m_Position);
        Renderer::Submit(m_Shield->GetVertexData()->m_Shader, m_Shield);
        if(Input::IsKeyDown(GLFW_KEY_SPACE))
        {
            m_Shield->GetBounding()->SetNeedTest(true);
            m_BoundingVolume = m_Shield;
        }
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