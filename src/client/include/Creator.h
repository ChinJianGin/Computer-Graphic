#pragma once

#include"../../graphic/Shape.h"

namespace CustomSpace
{
    class ShapeFactory
    {
        public:
            ShapeFactory();

            template<typename T>
            Ref<Shape> ShapeCreator();

        private:

            void CalculateIndices(Shape::ShapeType type, std::vector<GLuint>& indices);
    };

    inline void ShapeFactory::CalculateIndices(Shape::ShapeType type, std::vector<GLuint>& indices)
    {
        switch (type)
        {
        case Shape::ShapeType::None:
            CORE_WARN("Not set shape type.");
            break;
        case Shape::ShapeType::Point:
            indices.resize(1);
            indices.push_back(0);
            break;
        case Shape::ShapeType::Line:
            indices.resize(2);
            indices.push_back(0);
            indices.push_back(1);
            break;
        case Shape::ShapeType::Sphere:

            break;
        case Shape::ShapeType::Triangle:
            indices.resize(3);
            indices.push_back(0);
            indices.push_back(1);
            indices.push_back(2);
            break;
        case Shape::ShapeType::Quad:
            indices.resize(6);
            indices.push_back(0);
            indices.push_back(1);
            indices.push_back(2);
            indices.push_back(2);
            indices.push_back(3);
            indices.push_back(1);
            break;
        default:
            break;
        }
        CORE_WARN("Set Indices");
    }
    template<typename T>
    inline Ref<Shape>  ShapeFactory::ShapeCreator()
    {
        Ref<Shape> TemShape = CreateRef<T>();

        Ref<VAO> TempVAO = CreateRef<VAO>();

        Ref<VBO> TempVBO = VBO::Create(&(TemShape->GetPointsData()->Points.front()), sizeof(GLfloat) * TemShape->GetPointsData()->Points.size());

        BufferLayout TempLayout;
        if(TemShape->GetType() == Shape::ShapeType::Triangle)
        {
            TempLayout = 
            {
                {ShaderDataType::f_Vec3, "vPosition"},
                {ShaderDataType::f_Vec3, "vColor"}
            };
        }
        else
        {
            TempLayout = 
            {
                {ShaderDataType::f_Vec3, "vPosition"},
                {ShaderDataType::f_Vec3, "vColor"}
            };   
        }
        TempVBO->SetLayout(TempLayout);
        TempVAO->AddVBO(TempVBO);

        std::vector<GLuint> Indices;
        this->CalculateIndices(TemShape->GetType(), Indices);

       Ref<EBO> TempEBO =  EBO::Create(&(Indices.front()), sizeof(GLuint) * Indices.size());
       TempVAO->SetEBO(TempEBO);


       Ref<Shader> ShaderProgram = CreateRef<Shader>(Shader("../src/shader/2DGame.vert", "../src/shader/2DGame.frag"));

       TemShape->GetVertexData()->m_VAO = TempVAO;
       TemShape->GetVertexData()->m_VBO = TempVBO;
       TemShape->GetVertexData()->m_Shader = ShaderProgram;

       return TemShape;
    }
}