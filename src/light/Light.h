#pragma once
#include"../core/include/Core.h"
#include"../graphic/Shape.h"

namespace CustomSpace
{
    struct LightData
    {
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 position;
        glm::vec3 halfvector;
        glm::vec3 spotTarget;
        glm::vec3 direction;
        float spotExponent;
        float spotCutoff;
        float spotCosCutoff;
        float constantAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;
    };

    struct Attenuation
    {
        float linear;
        float quadratic;
    };
    class Light
    {
        public:
            Light() {}
            virtual ~Light() = default;

            virtual void Init() = 0;

            virtual void SetPosition(const glm::vec3& pos) = 0;
            virtual void SetModelMatrix(const glm::mat4& model) = 0;

            virtual void SetDirection(const glm::vec3& dir) = 0;

            virtual void SetAmbient(const glm::vec3& amb) = 0;
            virtual void SetDiffuse(const glm::vec3& diff) = 0;
            virtual void SetSpecular(const glm::vec3& spec) = 0;

            virtual const Ref<Shape> GetBody() { return m_Body; }
            virtual const Ref<Transform> GetTransform() { return m_Body->GetTransform(); }

            virtual const Ref<LightData> GetLightData() { return m_Data; }

        protected:
            Ref<Shape> m_Body;
            Ref<LightData> m_Data;
    };
}