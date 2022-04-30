#pragma once
#include"./Actor.h"

namespace CustomSpace
{
    class Projectile : public Actor
    {
        public:
        Projectile();
        virtual ~Projectile() = default;

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
        virtual Ref<BoundingObject> GetBounding() const override { return this->m_Body->GetBounding(); }

        virtual void ModelMatrixMethod(const Shape::MatrixMethod method = Shape::MatrixMethod::TRS) override;

        enum class TeamID : uint8_t
        {
            Neutral = 0, Player = 1, Enemy = 2
        };

        void SetTeamID(const TeamID id);
        TeamID GetID() const { return m_TeamID; }

        void Active();

        void Reset();

        Ref<Shape> GetBody() const { return this->m_Body; }
        protected:
        virtual void AttackAction() override;

        TeamID m_TeamID;
    };
}