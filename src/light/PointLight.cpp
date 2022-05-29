#include"./PointLight.h"
#include"../client/include/Creator.h"
#include"../graphic/LightBox.h"

namespace CustomSpace
{
    PointLight::PointLight()
    {
        this->Init();
    }

    void PointLight::Init()
    {
        m_Body = ShapeFactory::Get().ShapeCreator<LightBox>();
        m_Data = CreateRef<LightData>();
        m_Data->ambient = glm::vec3(.2f, .2f, .2f);
        m_Data->diffuse = glm::vec3(.5f, .5f, .5f);
        m_Data->specular = glm::vec3(1.f, 1.f, 1.f);
        m_Attenuation = CreateRef<Attenuation>();
        m_Attenuation->linear = .09f;
        m_Attenuation->quadratic = .032f;
    }

    void PointLight::SetPosition(const glm::vec3& pos)
    {
        m_Body->SetPosition(pos);
    }

    void PointLight::SetModelMatrix(const glm::mat4& model)
    {
        m_Body->SetModelMatrix(model);
    }

    void PointLight::SetDirection(const glm::vec3& dir)
    {

    }

    void PointLight::SetAmbient(const glm::vec3& amb)
    {
        m_Data->ambient = amb;
    }

    void PointLight::SetDiffuse(const glm::vec3& diff)
    {
        m_Data->diffuse = diff;
    }

    void PointLight::SetSpecular(const glm::vec3& spec)
    {
        m_Data->specular = spec;
    }

    void PointLight::SetLinear(const float linear)
    {
        m_Attenuation->linear = linear;
    }

    void PointLight::SetQuadratic(const float quadratic)
    {
        m_Attenuation->quadratic = quadratic;
    }
}