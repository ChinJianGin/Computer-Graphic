#include "../include/Creator.h"


namespace CustomSpace
{
    ShapeFactory::ShapeFactory()
    {

    }


    template<typename T>
    Ref<T>  ShapeFactory::ShapeCreator()
    {
        Ref<Shape> TemShape = CreateRef<T>();

        Ref<VAO> TempVAO = CreateRef<VAO>();

        Ref<VBO> TempVBO = VBO::Create(&(TemShape->GetPointsData()->Points.front()), sizeof(glm::vec3) * TemShape->GetPointsData()->Points.size());

        BufferLayout TempLayout = 
        {
           {ShaderDataType::f_Vec3, "vPosition"},
           {ShaderDataType::f_Vec3, "vColor"}
        };

        TempVBO->SetLayout(TempLayout);
        TempVAO->AddVBO(TempVBO);

        std::vector<GLuint>* Indices;
        this->CalculateIndices(TemShape->GetType(), Indices);

       Ref<EBO> TempEBO =  EBO::Create(&(Indices->front()), sizeof(GLuint) * Indices->size());
       TempVAO->SetEBO(TempEBO);

       Ref<Shader> ShaderProgram = CreateRef<Shader>(Shader("../src/shader/2DGame.vert", "../src/shader/2DGame.frag"));

       TemShape->m_VertexData->m_VAO = TempVAO;
       TemShape->m_VertexData->m_VBO = TempVBO;
       TemShape->m_VertexData->m_Shader = ShaderProgram;

       return TemShape;
    }
}