#include"./ShaderPool.h"

ShaderPool* ShaderPool::Instance = nullptr;

ShaderPool::ShaderPool()
{
    Instance = this;
}

ShaderPool::~ShaderPool()
{
    m_ShaderPool.clear();
    delete Instance;
}

CustomSpace::Ref<Shader>& ShaderPool::getShader(const int key)
{
    if(m_ShaderPool.find(key) != m_ShaderPool.end())
    {
        return m_ShaderPool[key];
    }
    else
        return this->getShader(key, "../src/shader/2DGame.vert", "../src/shader/2DGame.frag");
}

CustomSpace::Ref<Shader>& ShaderPool::getShader(const int key, const char* vert, const char* frag)
{
    if(m_ShaderPool.find(key) != m_ShaderPool.end())
    {
        return m_ShaderPool[key];
    }
    CustomSpace::Ref<Shader> _Shader = CustomSpace::CreateRef<Shader>(Shader(vert, frag));
    m_ShaderPool.insert(std::pair<int, CustomSpace::Ref<Shader>>(key, _Shader));
    return m_ShaderPool[key];
}
CustomSpace::Ref<Shader>& ShaderPool::getShader(const int key, const char* vert, const char* frag, const char* geom)
{
    if(m_ShaderPool.find(key) != m_ShaderPool.end())
    {
        return m_ShaderPool[key];
    }
    CustomSpace::Ref<Shader> _Shader = CustomSpace::CreateRef<Shader>(Shader(vert, frag, geom));
    m_ShaderPool.insert(std::pair<int, CustomSpace::Ref<Shader>>(key, _Shader));
    return m_ShaderPool[key];
}