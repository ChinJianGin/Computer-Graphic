#pragma once
#include"./Actor.h"
#include"../../core/include/KeyEvent.h"

namespace CustomSpace
{
    class APlayer : public Actor
    {
        public:
        APlayer(const Ref<ShapeFactory>& factory);
        virtual ~APlayer() = default;

        virtual void Init(const Ref<ShapeFactory>& fctory) override;
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
        virtual Ref<BoundingObject> GetBounding() const override { return this->m_BoundingVolume->GetBounding(); }

        virtual void ModelMatrixMethod(const Shape::MatrixMethod method = Shape::MatrixMethod::TRS) override;

        virtual void AttackAction() override;

        void OnEvent(Event& event);

        bool OnKeyPressedEvent(KeyPressedEvent& event);

        virtual void Dead() override;
        virtual void TakeDamage() override;

        void SetTarget(const Ref<Actor> target) { m_Target = target; }
        private:
        Ref<Texture2D> m_PlayerTex, m_ShieldTex, m_SatelliteTex, m_HitTex;
        Ref<Shape> m_Shield, m_Satellite[2];
        Ref<Shape> m_BoundingVolume;
        Ref<Shape> m_Hit;

        glm::vec3 m_PlayerOriginPosition;

        float m_Orbit = 0;

        bool ActiveShiled = false, AttackAgain = false;
        float EffectTime = 0, ShiledCooldown = -1.f, SAT = 1.f;

        void ShieldRender();

        bool damage = false;
        float damagetime = 0;

        bool b_LaunchRocket = false;
        float RocketSAT = 0.005f, RocketCAL = 0;

        bool b_LowHP = false;
        bool b_Launch = false;

        int RocketCount = 0;
        protected:

        Ref<Actor> m_Target = nullptr;
    };
}