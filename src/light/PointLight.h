#pragma once
#include"./Light.h"

namespace CustomSpace
{
    class PointLight : public Light
    {
        public:
        virtual void Init() override;

        virtual void SetPosition(const glm::vec3& pos) override;
        virtual void SetModelMatrix(const glm::mat4& model) override;

        virtual void SetDirection(const glm::vec3& dir) override;
        virtual void SetAmbient(const glm::vec3& amb) override;
        virtual void SetDiffuse(const glm::vec3& diff) override;
        virtual void SetSpecular(const glm::vec3& spec) override;

        void SetLinear(const float linear);
        void SetQuadratic(const float quadratic);

        float GetLinear() const { return this->m_Attenuation->linear; }
        float GetQuadratic() const { return this->m_Attenuation->quadratic; }

        PointLight();
        virtual ~PointLight() = default;

        private:
        Ref<Attenuation> m_Attenuation;
    };
}