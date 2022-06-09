#include"./PortalDoor.h"
#include"../shader/ShaderPool.h"

namespace CustomSpace
{
    PortalDoor::PortalDoor()
    {
        this->Init();
    }

    void PortalDoor::Init()
    {
        m_Transform = CreateRef<Transform>();

        m_Model[0] = CreateRef<Model>("../src/Model/portaldoor/portaldoor_root.obj");

        m_Model[1] = CreateRef<Model>("../src/Model/portaldoor/portaldoor_left.obj");

        m_Model[2] = CreateRef<Model>("../src/Model/portaldoor/portaldoor_right.obj");

        glm::mat4 model = glm::mat4(1.f);

        model = glm::translate(glm::mat4(1.f), glm::vec3(0.f));
        model = glm::rotate(model, glm::radians(0.f), glm::vec3(1, 0, 0));
        model = glm::scale(model, glm::vec3(1.f));

        m_Transform->SetModelMatrix(model);

        m_local_left = glm::translate(model, glm::vec3(0.f));
        m_local_left = glm::rotate(model, glm::radians(0.f), glm::vec3(1, 0, 0));
        m_local_left = glm::scale(model, glm::vec3(1.f));

        model = m_Transform->GetModelMatrix();

        m_local_right = glm::translate(model, glm::vec3(0.f));
        m_local_right = glm::rotate(model, glm::radians(0.f), glm::vec3(1, 0, 0));
        m_local_right = glm::scale(model, glm::vec3(1.f));
    }

    void PortalDoor::Update(CoreTimer& timer)
    {
        Ref<Shader> _shader = ShaderPool::Get().getShader(1);
        _shader->Activate();
        _shader->SetMat4("uMV", m_Transform->GetModelMatrix());
        _shader->SetInt("HaveTex", true);
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_Transform->GetModelMatrix())));
        m_Model[0]->Draw(*_shader);


        _shader->SetMat4("uMV", m_local_left);
        _shader->SetInt("HaveTex", true);
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_local_left)));
        m_Model[1]->Draw(*_shader);

        _shader->SetMat4("uMV", m_local_right);
        _shader->SetInt("HaveTex", true);
        _shader->SetMat3("uULMM", glm::inverseTranspose(glm::mat3(m_local_right)));
        m_Model[2]->Draw(*_shader);
    }

    void PortalDoor::SetModelMatrix(glm::mat4& model)
    {
        m_Transform->SetModelMatrix(model);
        b_IsDirty = true;
    }

    void PortalDoor::SetPosition(glm::vec3& pos)
    {
        m_Transform->SetPosition(pos);
        b_IsDirty = true;
    }

    void PortalDoor::SetRotation(float radians, glm::vec3& axis)
    {
        m_Transform->SetRotation(radians, axis);
        b_IsDirty = true;
    }

    void PortalDoor::SetScale(glm::vec3& scale)
    {
        m_Transform->SetScaleValue(scale);
        b_IsDirty = true;
    }

    void PortalDoor::LocalUpdate()
    {

    }
}