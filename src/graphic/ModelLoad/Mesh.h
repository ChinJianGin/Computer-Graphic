#pragma once
#include"../../core/include/Core.h"

namespace CustomSpace
{
    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoord;
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

        private:
            unsigned int m_VAO, m_VBO, m_EBO;
            std::vector<Vertex> m_vertices;
            std::vector<unsigned int> m_indices;
            std::vector<Texture_str> m_textures;

            

            void Init();
    };
}