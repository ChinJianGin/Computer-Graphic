#pragma once
#include"../core/include/Core.h"
#include "../vertex/VAO.h"

namespace CustomSpace
{
    struct Transform
    {
        glm::mat4 m_ModelMatrix;
        glm::vec3 m_Position;
        float m_Rotation;
        float m_Scale;

        Transform(const glm::vec3& pos = glm::vec3(0), float rotation = 0, float scale = 1)
        : m_Position(pos), m_Rotation(rotation), m_Scale(scale)
        {
            m_ModelMatrix = glm::translate(glm::mat4(1.f), pos)
             * glm::rotate(glm::mat4(1.f), m_Rotation, glm::vec3(1, 1, 1))
             * glm::scale(glm::mat4(1.f), glm::vec3(m_Scale));
        }
    };

    struct PointsData
    {
        const glm::vec3* Points;

        PointsData(const glm::vec3* point)
        {
            Points = point;
        }
    };

    struct VertexData
    {
        Ref<VAO> m_VAO;
        Ref<VBO> m_VBO;
    };
   
    class Shape
    {
        public:
            virtual void Init() = 0;

            virtual void SetPoints(const Ref<PointsData>& data) = 0;
            virtual void SetTransform(const Ref<Transform>& trans) = 0;
            virtual void SetPosition(const glm::vec3& pos) = 0;
            virtual void SetColor(const glm::vec4 color[]) = 0;
            virtual void SetRotation(const float rotation) = 0;
            virtual void SetScale(const float scale) = 0;

            virtual Ref<Transform> GetTransform() const = 0;  
            virtual Ref<PointsData> GetPointsData() const = 0;
            virtual Ref<VertexData> GetVertexData() const = 0;   
            virtual void GetColor(glm::vec4 colors[]) = 0; 
            Shape();

            virtual ~Shape() = default;      
        protected:
            Ref<Transform> m_Transform;
            Ref<PointsData> m_PointsData;
            Ref<VertexData> m_VertexData;

            glm::vec4 m_Color[4];
        private:
            virtual void LocalUpdate() = 0;
    };
} // namespace CustomSpace
