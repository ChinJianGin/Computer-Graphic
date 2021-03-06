#pragma once
#include"./Light.h"

namespace CustomSpace
{
    class SpotLight : public Light
    {
        public:
        SpotLight();
        virtual ~SpotLight() = default;

        virtual void Init() override;
        virtual void SetPosition(const glm::vec3& pos) override;
        virtual void SetModelMatrix(const glm::mat4& model) override;

        virtual void SetDirection(const glm::vec3& dir) override;
        virtual void SetAmbient(const glm::vec3& amb) override;
        virtual void SetDiffuse(const glm::vec3& diff) override;
        virtual void SetSpecular(const glm::vec3& spec) override;

        void SetLinear(const float linear);
        void SetQuadratic(const float quadratic);

        void SetInnerCutOff(const float inner);
        void SetOuterCutOff(const float outer);

        float GetLinear() const { return this->m_Attenuation->linear; }
        float GetQuadratic() const { return this->m_Attenuation->quadratic; }
        float GetInner() const { return this->m_InnerCutOff; }
        float GetOuter() const { return this->m_OuterCutOff; }

        private:
        Ref<Attenuation> m_Attenuation;
        float m_InnerCutOff, m_OuterCutOff;
    };
}