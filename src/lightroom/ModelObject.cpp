#include"./ModelObject.h"

namespace CustomSpace
{
    ModelObject::ModelObject(const char* path)
    {
        this->Init(path);
    }

    ModelObject::~ModelObject()
    {

    }

    void ModelObject::Init(const char* path)
    {
        m_Transform = CreateRef<Transform>();
        m_Model = CreateRef<Model>(path);
    }

    void ModelObject::Update(Shader& shader)
    {
        m_Model->Draw(shader);
    }

    void ModelObject::UpdateWithNormal(Shader& shader, bool normal)
    {
        m_Model->DrawWithNormalMap(shader, normal);
    }

    void ModelObject::SetModelMatrix(const glm::mat4& model)
    {
        m_Transform->SetModelMatrix(model);
    }

    void ModelObject::SetPosition(const glm::vec3& pos)
    {
        m_Transform->SetPosition(pos);
    }

    void ModelObject::SetRotation(const float radians, const glm::vec3& axis)
    {
        m_Transform->SetRotation(radians, axis);
    }

    void ModelObject::SetScale(const glm::vec3& scale)
    {
        m_Transform->SetScaleValue(scale);
    }

    void ModelObject::SetParent(const Ref<Transform>& parent)
    {
        m_Transform->SetParentTransform(parent);
    }
}