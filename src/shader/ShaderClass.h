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
        GLuint ID;
        Shader(const char* vertexfile, const char* fragmentfile);

        void Activate();
        void Delete();

        void UpdateUniform(const char* name, const glm::mat4 matrix);
    private:
        void CompileErrors(unsigned int shader, const char* type);
};