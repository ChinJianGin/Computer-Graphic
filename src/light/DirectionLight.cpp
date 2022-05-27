#include"./DirectionLight.h"
#include"../client/include/Creator.h"
namespace CustomSpace
{
    DirectionLight::DirectionLight()
    {
        this->Init();
    }

    void DirectionLight::Init()
    {
        m_Body = ShapeFactory::Get().ShapeCreator<Box>();
        m_Data = CreateRef<LightData>();
        m_Data->direction = glm::vec3(0.f, 0.f, -1.f);
        m_Data->ambient = glm::vec3(.2f, .2f, .2f);
        m_Data->diffuse = glm::vec3(.5f, .5f, .5f);
        m_Data->specular = glm::vec3(1.f, 1.f, 1.f);
    }

    void DirectionLight::SetPosition(const glm::vec3& pos)
    {
        m_Body->SetPosition(pos);
    }

    void DirectionLight::SetModelMatrix(const glm::mat4& model)
    {
        m_Body->SetModelMatrix(model);
    }

    void DirectionLight::SetDirection(const glm::vec3& dir)
    {
        m_Data->direction = dir;
    }

    void DirectionLight::SetAmbient(const glm::vec3& amb)
    {
        m_Data->ambient = amb;
    }

    void DirectionLight::SetDiffuse(const glm::vec3& diff)
    {
        m_Data->diffuse = diff;
    }

    void DirectionLight::SetSpecular(const glm::vec3& spec)
    {
        m_Data->specular = spec;
    }
}