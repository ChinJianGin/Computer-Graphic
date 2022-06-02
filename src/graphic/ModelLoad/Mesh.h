#pragma once
#include"../../core/include/Core.h"

namespace CustomSpace
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
        glm::vec3 Tangent;
    };

    struct Texture_str
    {
        unsigned int id;
        std::string type;
        std::string path;
    };

    class Mesh
    {
        public:

            Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture_str> textures);
            void Draw(Shader& shader);

            void HaveNormalMap(bool have) { this->b_HaveNormalMap = have; }
        private:
            unsigned int m_VAO, m_VBO, m_EBO;
            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<Texture_str> m_textures;

            bool b_HaveNormalMap = false;

            

            void Init();
    };
}