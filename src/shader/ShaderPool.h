#pragma once
#include"./ShaderClass.h"

class ShaderPool
{
    public:
    ShaderPool();
    ~ShaderPool();

    static ShaderPool& Get() { return *Instance; }
    CustomSpace::Ref<Shader>& getShader(const int key);
    CustomSpace::Ref<Shader>& getShader(const int key, const char* vert, const char* frag);

    private:
        static ShaderPool* Instance;
        std::map<int, CustomSpace::Ref<Shader>> m_ShaderPool;
};