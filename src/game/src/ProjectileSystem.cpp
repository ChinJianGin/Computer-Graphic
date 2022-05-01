#include"../include/ProjectileSystem.h"

namespace CustomSpace
{
    Scope<ProjectileSystem> ProjectileSystem::m_ProjectileSystem = nullptr;

    Scope<ProjectileSystem>& ProjectileSystem::GetProjectileSystem(const Ref<ShapeFactory>& factory)
    {
        if(m_ProjectileSystem == nullptr)
        {
            m_ProjectileSystem = CreateScope<ProjectileSystem>(factory);
        }
        return m_ProjectileSystem;
    }

    Scope<ProjectileSystem>& ProjectileSystem::GetProjectileSystem()
    {
        return m_ProjectileSystem;
    }

    ProjectileSystem::ProjectileSystem(const Ref<ShapeFactory>& factory)
    {
        m_ProjectileList = CreateScope<LinkList<Projectile*>>();
        m_InUsedList = CreateScope<LinkList<Projectile*>>();
        m_Projectiles = new Projectile[PROJECTILE_NUM];
        for(int i = 0; i < PROJECTILE_NUM; i++)
        {
            m_Projectiles[i].Init(factory);
            m_ProjectileList->Push_back(&m_Projectiles[i]);
        }
    }

    ProjectileSystem::~ProjectileSystem()
    {
        m_ProjectileList->Clear();
        delete[] m_Projectiles;
    }

    Scope<LinkList<Projectile*>>& ProjectileSystem::GetProjectileList()
    {
        return m_ProjectileList;
    }

    Scope<LinkList<Projectile*>>& ProjectileSystem::GetInUsedList()
    {
        return m_InUsedList;
    }
}