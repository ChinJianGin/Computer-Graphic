#pragma once

#include"./Enemy.h"

namespace CustomSpace
{
    class BossEnemy : public Enemy
    {
        public:
        BossEnemy(const Ref<ShapeFactory>& factory);
        virtual ~BossEnemy() = default;

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

        virtual void Behavior(const CoreTimer& timer) override;
        virtual void SetOriginPosition(const glm::vec3& origin) override;
        private:
        Ref<Texture2D> m_BossEnemyTex, m_BossGuardianTex;

        Ref<Shape> m_Guardian[2];
    };
}