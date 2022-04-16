#pragma once
#include"../core/include/Core.h"
#include "../vertex/VAO.h"

namespace CustomSpace
{
    struct Transform
    {
        glm::mat4 m_ModelMatrix;
        glm::vec3 m_Position;
        glm::vec3 m_Axis;
        float m_Rotation;
        float m_Scale;

        Transform(const glm::vec3& pos = glm::vec3(0), float rotation = 0, const glm::vec3& axis = glm::vec3(0, 0, 1), float scale = 1)
        : m_Position(pos), m_Rotation(rotation), m_Axis(axis), m_Scale(scale)
        {
            m_ModelMatrix = glm::translate(glm::mat4(1.f), pos)
             * glm::rotate(glm::mat4(1.f), m_Rotation, m_Axis)
             * glm::scale(glm::mat4(1.f), glm::vec3(m_Scale));
        }
    };

    struct PointsData
    {
        std::vector<GLfloat> Points;
    };

    struct VertexData
    {
        Ref<VAO> m_VAO;
        Ref<VBO> m_VBO;
        Ref<Shader> m_Shader;
    };
   
    class Shape
    {
        public:
            virtual void Init() = 0;

            virtual void SetPoints(const Ref<PointsData>& data) = 0;
            virtual void SetTransform(const Ref<Transform>& trans) = 0;
            virtual void SetPosition(const glm::vec3& pos) = 0;
            virtual void SetColor(const std::vector<glm::vec4> colors) = 0;
            virtual void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1)) = 0;
            virtual void SetScale(const float scale) = 0;

            virtual Ref<Transform> GetTransform() const = 0;  
            virtual Ref<PointsData> GetPointsData() const = 0;
            virtual Ref<VertexData> GetVertexData() const = 0;   
            virtual void GetColor(std::vector<glm::vec4>& colors) = 0; 

            enum class MatrixMethod
            {
                TRS = 0, RTS = 1, RTRS = 2
            };
            virtual void ModelMatrixMethod(const MatrixMethod method = MatrixMethod::TRS) = 0;

            enum class ShapeType
            {
                None = 0, Point = 1, Line = 2, Circle = 3, Triangle = 4, Quad = 5 
            };

            Shape();

            virtual ~Shape() = default;      

            ShapeType GetType() { return m_Type; }
        protected:
            Ref<Transform> m_Transform;
            Ref<PointsData> m_PointsData;
            Ref<VertexData> m_VertexData;

            std::vector<glm::vec4> m_Color;

            ShapeType m_Type;
            MatrixMethod m_Method;
        private:
            virtual void LocalUpdate() = 0;
    };
} // namespace CustomSpace
