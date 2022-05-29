#pragma once
#include"./Light.h"
#include"../graphic/LightBox.h"
namespace CustomSpace
{
    class DirectionLight : public Light
    {
        public:
        virtual void Init() override;

        virtual void SetPosition(const glm::vec3& pos) override;
        virtual void SetModelMatrix(const glm::mat4& model) override;

        virtual void SetDirection(const glm::vec3& dir) override;
        virtual void SetAmbient(const glm::vec3& amb) override;
        virtual void SetDiffuse(const glm::vec3& diff) override;
        virtual void SetSpecular(const glm::vec3& spec) override;

        DirectionLight();
        virtual ~DirectionLight() = default;
    };
}