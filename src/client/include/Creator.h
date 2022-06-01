#pragma once

#include"../../graphic/Shape.h"

namespace CustomSpace
{
    class ShapeFactory
    {
        public:
            ShapeFactory();

            static ShapeFactory& Get() { return *Instance; }

            template<typename T>
            static Ref<Shape> ShapeCreator();

        private:
            static ShapeFactory* Instance;
    };

    template<typename T>
    inline Ref<Shape>  ShapeFactory::ShapeCreator()
    {
        Ref<Shape> TemShape = CreateRef<T>();

        Ref<VAO> TempVAO = CreateRef<VAO>();

        Ref<VBO> TempVBO = VBO::Create(&(TemShape->GetPointsData()->Points.front()), sizeof(GLfloat) * TemShape->GetPointsData()->Points.size());

        BufferLayout TempLayout;
        Ref<Shader> ShaderProgram;
        if(TemShape->GetType() == Shape::ShapeType::Model)
        {
            TempLayout = 
            {
                {ShaderDataType::f_Vec3, "vPosition"},
                {ShaderDataType::f_Vec3, "vNormal"},
                {ShaderDataType::f_Vec2, "vTexCoord"},
                {ShaderDataType::f_Vec3, "vTangent"},
                {ShaderDataType::f_Vec3, "vBitangent"}
            };
        }
        else
        {
            if(TemShape->GetType() == Shape::ShapeType::Light)
            {
                TempLayout = 
                {
                    {ShaderDataType::f_Vec3, "vPosition"}
                };
            }
            else
            {
                TempLayout = 
                {
                    {ShaderDataType::f_Vec3, "vPosition"},
                    {ShaderDataType::f_Vec3, "vColor"},
                    {ShaderDataType::f_Vec2, "vTexCoord"}
                };
            }
        }
        TempVBO->SetLayout(TempLayout);
        TempVAO->AddVBO(TempVBO);

        Ref<EBO> TempEBO =  EBO::Create(&(TemShape->GetVertexData()->indices.front()), sizeof(GLuint) * (TemShape->GetVertexData()->indices.size()));
        TempVAO->SetEBO(TempEBO);

       TemShape->GetVertexData()->m_VAO = TempVAO;
       TemShape->GetVertexData()->m_VBO = TempVBO;

       return TemShape;
    }
}