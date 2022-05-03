#pragma once
#include"./Enemy.h"

namespace CustomSpace
{
    class NormalEnemy : public Enemy
    {
        public:
        NormalEnemy(const Ref<ShapeFactory>& factory);
        virtual ~NormalEnemy() = default;

        virtual void Init(const Ref<ShapeFactory>& factory) override;
        virtual void Update(const CoreTimer& timer) override;

        virtual void SetTransform(const Ref<Transform>& trans) override;
        virtual void SetPosition(const glm::vec3& pos) override;
        virtual void SetPosition(const float pos, int axis) override;
        virtual void SetColor(const std::vector<glm::vec4> colors) override;
        virtual void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1)) override;
        virtual void SetScale(const glm::vec3& scale) override;

        virtual Ref<Transform> GetTransform() const override { return this->m_Body->GetTransform(); }
        virtual Ref<PointsData> GetPointsData() const override { return this->m_Body->GetPointsData(); }
        virtual Ref<VertexData> GetVertexData() const override { return this->m_Body->GetVertexData(); }
        virtual Ref<BoundingObject> GetBounding() const override { return this->m_Body->GetBounding(); }

        virtual void ModelMatrixMethod(const Shape::MatrixMethod method = Shape::MatrixMethod::TRS) override;

        virtual void AttackAction() override;

        virtual void SetType(const EnemyType type) override;

        private:
        Ref<Texture2D> m_NormalEnemyTex;

        float m_SAT = 3.f, m_Cal =  0;
    };
}