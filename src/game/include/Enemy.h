#pragma once
#include"./Actor.h"
#include"./ProjectileSystem.h"

namespace CustomSpace
{
    class Enemy : public Actor
    {
        public:

        enum class EnemyType
        {
            Normal = 0, Elite = 1, Boss = 2
        } ;

        virtual void SetType(const EnemyType type) = 0;
        virtual EnemyType GetType() const { return m_Type; }

        virtual void SetTarget(const Ref<Actor> target) { m_Target = target;}
        protected:

        EnemyType m_Type;
        Ref<Actor> m_Target = nullptr;
    };
}