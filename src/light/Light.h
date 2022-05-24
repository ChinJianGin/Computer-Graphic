#pragma once
#include"../core/include/Core.h"
#include"../graphic/Shape.h"

namespace CustomSpace
{
    struct LightData
    {
        glm::vec4 ambient;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec3 position;
        glm::vec3 halfvector;
        glm::vec3 spotTarget;
        glm::vec3 spotDirection;
        float spotExponent;
        float spotCutoff;
        float spotCosCutoff;
        float constantAttenuation;
        float linearAttenuation;
        float quadraticAttenuation;
    };
    class Light
    {
        public:
            Light();
            virtual ~Light() = 0;

            virtual void Init() = 0;

            virtual const Ref<Shape>& GetBody() { return m_Body; }

        protected:
            Ref<Shape> m_Body;
            Ref<LightData> m_Data;
    };
}