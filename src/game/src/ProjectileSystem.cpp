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
        m_Projectiles = new Projectile[PROJECTILE_NUM];
        m_FreeList = CreateRef<SinglyLinkedList<Projectile*>>();
        m_UsedList = CreateRef<SinglyLinkedList<Projectile*>>();
        for(int i = 0; i < PROJECTILE_NUM; i++)
        {
            m_Projectiles[i].Init(factory);
            m_FreeList->push_back(&m_Projectiles[i]);
        }
        CORE_WARN("Free list : {0}", m_FreeList->size());
    }

    ProjectileSystem::~ProjectileSystem()
    {
        delete[] m_Projectiles;
    }

    Ref<SinglyLinkedList<Projectile*>> ProjectileSystem::GetFreeList()
    {
        return this->m_FreeList;
    }

    Ref<SinglyLinkedList<Projectile*>> ProjectileSystem::GetUsedList()
    {
        return this->m_UsedList;
    }
}