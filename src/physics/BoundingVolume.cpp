#include"BoundingVolume.h"

namespace CustomSpace
{
    BoundingObject::BoundingObject(const Ref<Transform>& trans, const Ref<PointsData>& points, bool isCircle)
    {
        this->Init(trans, points, isCircle);
    }

    void BoundingObject::Init(const Ref<Transform>& trans, const Ref<PointsData>& points, bool isCircle)
    {
        m_Circle = CreateRef<BoundingCircle>();
        float LocalScale = GetBiggerScale(trans->m_Scale);
        if(!isCircle)
        {
            m_Circle->m_Center = trans->m_Position;
            float Radius = ((points->Points[0] * points->Points[0]) + (points->Points[1] * points->Points[1])) * (LocalScale * LocalScale);
            m_Circle->Radius_NS = Radius; 
            m_OriginRadius = Radius;
        }
        else
        {
            m_Circle->m_Center = trans->m_Position;
            float Radius = (points->Points[0] * points->Points[0]) * (LocalScale * LocalScale);
            m_Circle->Radius_NS = Radius;
            m_OriginRadius = Radius;
        }
    }

    void BoundingObject::ResizeBoundingVolume(const Ref<Transform>& trans)
    {
        m_Circle->m_Center = trans->m_Position;
        float LocalScale = GetBiggerScale(trans->m_Scale);
        float TempRadius = m_OriginRadius * (LocalScale * LocalScale);
        m_Circle->Radius_NS = TempRadius;
        // CORE_TRACE("Position : (X:{0} , Y:{1}), Radius : {2}", m_Circle->m_Center.x, m_Circle->m_Center.y, m_Circle->Radius_NS);
    }

    bool BoundingObject::Intersects(const Ref<BoundingObject>& object)
    {
        if(!object->IsNeedTest())
        {
            return false;
        }
        else
        {
            float C1_R = this->m_Circle->Radius_NS;
            float C2_R = object->GetBoundingVolume()->Radius_NS;
            glm::vec2 v2_distance = object->GetBoundingVolume()->m_Center - this->m_Circle->m_Center;
            float f_distance = v2_distance.x * v2_distance.x + v2_distance.y * v2_distance.y;
            return f_distance <= (C1_R + C2_R);
        }
    }

    void BoundingObject::SetNeedTest(bool test)
    {
        b_NeedTest = test;
    }

    const Ref<BoundingObject::BoundingCircle> BoundingObject::GetBoundingVolume() const
    {
        return m_Circle;
    }

    const float BoundingObject::GetBiggerScale(const glm::vec3& scale) const
    {
        return scale.x >= scale.y ? scale.x : scale.y;
    } 
}