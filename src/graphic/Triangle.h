#pragma once
#include"./Shape.h"

namespace CustomSpace
{
    class Triangle : public Shape
    {
        public:
            virtual void Init() override;

            virtual void SetPoints(const Ref<VertexData>& data) override;
            virtual void SetTransform(const Ref<Transform>& trans) override;
            virtual void SetPosition(const glm::vec3& pos) override;
            virtual void SetColor(const glm::vec4 color[]) override;
            virtual void SetRotation(const float rotation) override;
            virtual void SetScale(const float scale) override;

            virtual Ref<Transform> GetTransform() const override { return this->m_Transform; }
            virtual Ref<VertexData> GetVertexData() const override { return this->m_VertexData; }
            virtual void GetColor(glm::vec4 colors[]) override { colors = m_Color; }
            Triangle();
            virtual ~Triangle() = default;
        protected:
            

            

        private:
            virtual void LocalUpdate() override;

    };
}