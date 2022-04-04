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
            indices.push_back(1);
            indices.push_back(2);
            indices.push_back(3);
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

    CORE_WARN("Create vao");
        Ref<VBO> TempVBO = VBO::Create(&(TemShape->GetPointsData()->Points.front()), sizeof(glm::vec3) * TemShape->GetPointsData()->Points.size());

    CORE_WARN("Create vbo");
        BufferLayout TempLayout = 
        {
           {ShaderDataType::f_Vec3, "vPosition"},
           {ShaderDataType::f_Vec3, "vColor"}
        };

    CORE_WARN("Create Layout");
        TempVBO->SetLayout(TempLayout);
    CORE_WARN("Set layout");
        TempVAO->AddVBO(TempVBO);
    CORE_WARN("Add vbo");

        std::vector<GLuint> Indices;
        this->CalculateIndices(TemShape->GetType(), Indices);
    CORE_WARN("Create Indices");

       Ref<EBO> TempEBO =  EBO::Create(&(Indices.front()), sizeof(GLuint) * Indices.size());
       TempVAO->SetEBO(TempEBO);


       Ref<Shader> ShaderProgram = CreateRef<Shader>(Shader("../src/shader/2DGame.vert", "../src/shader/2DGame.frag"));
    CORE_WARN("Create shader");

       TemShape->GetVertexData()->m_VAO = TempVAO;
    CORE_WARN("Set VAO");
       TemShape->GetVertexData()->m_VBO = TempVBO;
    CORE_WARN("Set VBO");
       TemShape->GetVertexData()->m_Shader = ShaderProgram;
    CORE_WARN("Set Shader");

       return TemShape;
    }
}