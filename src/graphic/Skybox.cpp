#include"./Skybox.h"

namespace CustomSpace
{
    Skybox::Skybox()
    {
        this->Init();
    }

    Skybox::~Skybox()
    {

    }

    void Skybox::Init()
    {
        GLfloat skyboxVertices[] =
            {
                -1.f, -1.f, 1.f,
                1.f, -1.f, 1.f,
                1.f, -1.f, -1.f,
                -1.f, -1.f, -1.f,
                -1.f, 1.f, 1.f, 
                1.f, 1.f, 1.f,
                1.f, 1.f, -1.f,
                -1.f, 1.f, -1.f
            };

        GLuint skyboxIndices[] =
        {
            1, 6, 2,
            6, 1, 5,

            0, 7, 4,
            7, 0, 3,

            4, 6, 5,
            6, 4, 7,

            0, 2, 3,
            2, 0, 1,

            0, 5, 1,
            5, 0, 4,

            3, 6, 7,
            6, 3, 2
        };
        std::string parentPath = "../src/TextureSrc/skybox_material/SunsetDSRHD";
        std::vector<std::string> path
        {
            parentPath + "lf.tga",
            parentPath + "rt.tga",
            parentPath + "up.tga",
            parentPath + "dn.tga",
            parentPath + "ft.tga",
            parentPath + "bk.tga"
        };

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_EBO);
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_Texture = SkyboxTexture::Create(path);
    }

    void Skybox::Draw()
    {
        glBindVertexArray(m_VAO);
        m_Texture->Bind();
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}