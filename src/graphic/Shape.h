#pragma once
#include"../core/include/Core.h"
#include "../vertex/VAO.h"

namespace CustomSpace
{
    struct Transform
    {
        glm::vec3 m_Position;
        float m_Rotation;
        float m_Scale;

        Transform(const glm::vec3& pos = glm::vec3(0), float rotation = 0, float scale = 1)
        : m_Position(pos), m_Rotation(rotation), m_Scale(scale)
        {
        }
    };

    struct VertexData
    {
        glm::vec3 Points[0];

        VertexData(const glm::vec3 point[], uint32_t count)
        {
            for(int i = 0; i < count; i++)
            {
                Points[i] = point[i];
            }            
        }
    };
   
    class Shape
    {
        public:
            virtual void Init() = 0;

            virtual void SetPoints(const Ref<VertexData>& data) = 0;
            virtual void SetTransform(const Ref<Transform>& trans) = 0;
            virtual void SetPosition(const glm::vec3& pos) = 0;
            virtual void SetColor(const glm::vec4 color[]) = 0;
            virtual void SetRotation(const float rotation) = 0;
            virtual void SetScale(const float scale) = 0;

            virtual Ref<Transform> GetTransform() const = 0;  
            virtual Ref<VertexData> GetVertexData() const = 0;   
            virtual void GetColor(glm::vec4 colors[]) = 0; 
            Shape();

            virtual ~Shape() = default;      
        protected:
            Ref<Transform> m_Transform;
            Ref<VertexData> m_VertexData;

            glm::vec4 m_Color[4];
        private:
            
    };
} // namespace CustomSpace
