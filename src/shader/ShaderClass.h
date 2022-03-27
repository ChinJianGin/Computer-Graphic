#pragma once

#include<glad/glad.h>
#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

#include"../core/include/Core.h"

std::string get_file_contents(const char* filename);

class Shader
{
    public:
        
        Shader(const char* vertexfile, const char* fragmentfile);

        void Activate();
        void Delete();

        void SetInt(const char* name, int value);
        void SetIntArray(const char* name, int* values, uint32_t count);
        void SetFloat(const char* name, float value);
        void SetFloat2(const char* name, const glm::vec2& value);
        void SetFloat3(const char* name, const glm::vec3& value);
        void SetFloat4(const char* name, const glm::vec4& value);

        void SetMat3(const char* name, const glm::mat3& value);
        void SetMat4(const char* name, const glm::mat4& value);

        void UpdateUniformInt(const char* name, int value);
        void UpdateUniformIntArray(const char* name, int* values, uint32_t count);

        void UpdateUniformFloat(const char* name, float value);
        void UpdateUniformFloat2(const char* name,const glm::vec2& value);
        void UpdateUniformFloat3(const char* name, const glm::vec3& value);
        void UpdateUniformFloat4(const char* name, const glm::vec4& value);

        void UpdateUniformMat3(const char* name, const glm::mat3& matrix);
        void UpdateUniformMat4(const char* name, const glm::mat4& matrix);

        void UpdateUniform(const char* name, const glm::mat4 matrix);
    private:
        GLuint ID;

        void CompileErrors(unsigned int shader, const char* type);
};