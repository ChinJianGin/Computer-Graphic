#pragma once

#include"./Shape.h"

namespace CustomSpace
{
    class Line : public Shape
    {
        public:
            Line();
            virtual ~Line() =  default;
            virtual void Init() override;

            virtual void SetPoints(const Ref<PointsData>& data) override;
            virtual void SetTransform(const Ref<Transform>& trans) override;
            virtual void SetPosition(const glm::vec3& pos) override;
            virtual void SetPosition(const float pos, int axis) override;
            virtual void SetColor(const std::vector<glm::vec4> colors) override;
            virtual void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1)) override;
            virtual void SetScale(const glm::vec3& scale) override;

            virtual Ref<Transform> GetTransform() const override { return this->m_Transform; }
            virtual Ref<PointsData> GetPointsData() const override { return this->m_PointsData; }
            virtual Ref<VertexData>  GetVertexData() const override { return this->m_VertexData; }
            virtual Ref<BoundingObject> GetBounding() const override { return this->m_Bounding; }
            virtual void GetColor(std::vector<glm::vec4>& colors) override { colors.assign(m_Color.begin(), m_Color.end()); };

            virtual void ModelMatrixMethod(const MatrixMethod method = MatrixMethod::TRS) override;

            float GetLineWidth() const;
            void SetLineWidth(const GLfloat width);
        protected:

        private:
            virtual void LocalUpdate() override;
            GLfloat m_LineWidth = 1.f;
    };
}