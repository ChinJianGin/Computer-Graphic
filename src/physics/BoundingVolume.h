#pragma once

#include"../core/include/Core.h"
namespace CustomSpace
{
    class BoundingObject
    {
        public:
            BoundingObject(const Ref<Transform>& trans, const Ref<PointsData>& points, bool isCirecle = false);

            struct BoundingCircle
            {
                glm::vec2 m_Center;
                float Radius_NS;
            };
            void Init(const Ref<Transform>& trans, const Ref<PointsData>& points, bool isCircle);
            void ResizeBoundingVolume(const Ref<Transform>& trans);

            bool Intersects(const Ref<BoundingObject>& object);
            
            void SetNeedTest(bool test);
            const bool IsNeedTest() const { return b_NeedTest; }

            const Ref<BoundingCircle> GetBoundingVolume() const;
        private:

            Ref<BoundingCircle> m_Circle;

            float m_OriginRadius = 0;
            bool b_NeedTest = false;
        protected:

    };
}