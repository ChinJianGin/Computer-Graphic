#pragma once
#include"../../core/include/Core.h"
#include"./Mesh.h"

namespace CustomSpace
{
    class Model
    {
        public:
            Model(const char *path)
            {
                loadModel(path);
            }

            void Draw(Shader& shader);
            void DrawWithNormalMap(Shader& shader, bool normal = false);

        private:
            std::vector<Texture_str> textures_loaded;
            std::vector<Mesh> m_Meshes;
            std::string m_Directory;
            bool gammaCorection;

            void loadModel(std::string path);
            void processNode(aiNode* node, const aiScene* scene);
            Mesh processMesh(aiMesh* mesh, const aiScene* scene);
            std::vector<Texture_str> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    };
}