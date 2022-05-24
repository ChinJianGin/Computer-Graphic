#pragma once
#include"../core/include/Core.h"
#include "../vertex/VAO.h"
#include"../physics/BoundingVolume.h"

namespace CustomSpace
{
    struct VertexData
    {
        Ref<VAO> m_VAO;
        Ref<VBO> m_VBO;

        std::vector<GLuint> indices;
    };
    class Shape
    {
        public:
            virtual void Init() = 0;

            virtual void SetPoints(const Ref<PointsData>& data) = 0;
            virtual void SetPosition(const glm::vec3& pos) = 0;
            virtual void SetColor(const std::vector<glm::vec4> colors) = 0;
            virtual void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1)) = 0;
            virtual void SetScale(const glm::vec3& scale) = 0;
            virtual void SetModelMatrix(const glm::mat4& model) = 0;

            virtual void SetParentTransform(const Ref<Transform>& parent) = 0;

            virtual Ref<Transform> GetTransform() const = 0;  
            virtual Ref<PointsData> GetPointsData() const = 0;
            virtual Ref<VertexData> GetVertexData() const = 0;   
            virtual Ref<BoundingObject> GetBounding() const = 0;
            virtual void GetColor(std::vector<glm::vec4>& colors) = 0; 

            enum class ShapeType
            {
                None = 0, Point = 1, Line = 2, Circle = 3, Triangle = 4, Quad = 5, Model = 6, Light = 7
            };

            Shape();

            virtual ~Shape() = default;      

            ShapeType GetType() { return m_Type; }
        protected:
            Ref<Transform> m_Transform;
            Ref<PointsData> m_PointsData;
            Ref<VertexData> m_VertexData;
            Ref<BoundingObject> m_Bounding;

            std::vector<glm::vec4> m_Color;

            ShapeType m_Type;
        private:
    };
} // namespace CustomSpace
