#pragma once
#include"./3DModel.h"

namespace CustomSpace
{
    class LightBox : public CustomModel
    {
        public:
            virtual void Init() override;

            virtual void SetPoints(const Ref<PointsData>& data) override;
            virtual void SetPosition(const glm::vec3& pos) override;
            virtual void SetColor(const std::vector<glm::vec4> colors) override;
            virtual void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1)) override;
            virtual void SetScale(const glm::vec3& scale) override;
            virtual void SetModelMatrix(const glm::mat4& model) override;

            virtual void SetParentTransform(const Ref<Transform>& parent) override;

            virtual Ref<Transform> GetTransform() const override { return this->m_Transform; }
            virtual Ref<PointsData> GetPointsData() const override { return this->m_PointsData; }
            virtual Ref<VertexData> GetVertexData() const override { return this->m_VertexData; }
            virtual Ref<BoundingObject> GetBounding() const override { return this->m_Bounding; }
            virtual void GetColor(std::vector<glm::vec4>& colors) override { colors.assign(m_Color.begin(), m_Color.end()); }

            LightBox();
            virtual ~LightBox() = default;
    };
}