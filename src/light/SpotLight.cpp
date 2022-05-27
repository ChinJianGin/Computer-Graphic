#include"./SpotLight.h"
#include "../client/include/Creator.h"
#include "../graphic/Box.h"

namespace CustomSpace
{
    SpotLight::SpotLight()
    {
        this->Init();
    }

    void SpotLight::Init()
    {
        m_Body = ShapeFactory::Get().ShapeCreator<Box>();
        m_Data = CreateRef<LightData>();
        m_Data->ambient = glm::vec3(.2f, .2f, .2f);
        m_Data->diffuse = glm::vec3(.5f, .5f, .5f);
        m_Data->specular = glm::vec3(1.f, 1.f, 1.f);
        m_Data->direction = glm::vec3(0.f, -1.f, 0.f);
        m_Attenuation = CreateRef<Attenuation>();
        m_Attenuation->linear = .09f;
        m_Attenuation->quadratic = .032f;
        m_InnerCutOff = glm::cos(glm::radians(12.5f));
        m_OuterCutOff = glm::cos(glm::radians(17.5f));
    }

    void SpotLight::SetPosition(const glm::vec3 &pos)
    {
        m_Body->SetPosition(pos);
    }

    void SpotLight::SetModelMatrix(const glm::mat4 &model)
    {
        m_Body->SetModelMatrix(model);
    }

    void SpotLight::SetDirection(const glm::vec3 &dir)
    {
        m_Data->direction = dir;
    }

    void SpotLight::SetAmbient(const glm::vec3 &amb)
    {
        m_Data->ambient = amb;
    }

    void SpotLight::SetDiffuse(const glm::vec3 &diff)
    {
        m_Data->diffuse = diff;
    }

    void SpotLight::SetSpecular(const glm::vec3 &spec)
    {
        m_Data->specular = spec;
    }

    void SpotLight::SetLinear(const float linear)
    {
        m_Attenuation->linear = linear;
    }

    void SpotLight::SetQuadratic(const float quadratic)
    {
        m_Attenuation->quadratic = quadratic;
    }

    void SpotLight::SetInnerCutOff(const float inner)
    {
        m_InnerCutOff = glm::cos(glm::radians(inner));
    }

    void SpotLight::SetOuterCutOff(const float outer)
    {
        m_OuterCutOff = glm::cos(glm::radians(outer));
    }
}
