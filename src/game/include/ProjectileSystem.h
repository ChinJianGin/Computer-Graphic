#pragma once

#include"../../core/include/Core.h"
#include"./Projectile.h"

constexpr int PROJECTILE_NUM = 100;

namespace CustomSpace
{
    class ProjectileSystem
    {
        public:
        ProjectileSystem(const Ref<ShapeFactory>& factory);
        ~ProjectileSystem();
        static Scope<ProjectileSystem>& GetProjectileSystem(const Ref<ShapeFactory>& factory);
        static Scope<ProjectileSystem>& GetProjectileSystem();


        Scope<LinkList<Projectile*>>& GetProjectileList();
        Scope<LinkList<Projectile*>>& GetInUsedList();
        private:
        static Scope<ProjectileSystem> m_ProjectileSystem;
        Scope<LinkList<Projectile*>> m_ProjectileList;
        Scope<LinkList<Projectile*>> m_InUsedList;

        Projectile* m_Projectiles;
    };
}