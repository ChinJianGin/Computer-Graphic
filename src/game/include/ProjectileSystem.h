#pragma once

#include"../../core/include/Core.h"
#include"./Projectile.h"

constexpr int PROJECTILE_NUM = 300;

namespace CustomSpace
{
    class ProjectileSystem
    {
        public:
        ProjectileSystem(const Ref<ShapeFactory>& factory);
        ~ProjectileSystem();
        static Scope<ProjectileSystem>& GetProjectileSystem(const Ref<ShapeFactory>& factory);
        static Scope<ProjectileSystem>& GetProjectileSystem();

        Ref<SinglyLinkedList<Projectile*>> GetFreeList();
        Ref<SinglyLinkedList<Projectile*>> GetUsedList();
        private:
        static Scope<ProjectileSystem> m_ProjectileSystem;
        Ref<SinglyLinkedList<Projectile*>> m_FreeList;
        Ref<SinglyLinkedList<Projectile*>> m_UsedList;

        Projectile* m_Projectiles;
    };
}