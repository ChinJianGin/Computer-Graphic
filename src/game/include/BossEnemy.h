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

        virtual void Dead() override;
        virtual void TakeDamage() override;
        private:
        Ref<Texture2D> m_BossEnemyTex, m_BossGuardianTex, m_BossGaurdianTex180;

        Ref<Shape> m_Guardian[2];

        glm::vec3 m_OriginPosition = glm::vec3(0);

        void SecondState();
        bool b_Second = false;
        bool b_DoOnce = false;
        uint8_t AttackType = 0;
        uint8_t GaurdNum = 0;
        float m_RunTime = 0, m_SAT = 3, m_CAL = 0, m_TypeOneCal = 0, m_TypeOneSAT = .5f, m_InerCAL = 0;
        float m_GaurdSAT = 4.f, m_GaurdCAL = 0, m_GaurdPAT = .3f, m_GaurdIner = 0, m_GaurdPATC = 0;
        float m_SeconRunTime = 0;
    };
}