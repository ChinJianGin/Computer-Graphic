#pragma once

// Glad and GLFW
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Standard library
#include<iostream>
#include<math.h>
#include<array>
#include<vector>
#include<stdio.h>
#include<string>
#include<memory>

// GLM
#define GLM_EXT_INCLUDED
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace CustomSpace
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

// Custom
//#include"vector2.hpp"
//#include"vector3.hpp"
#include"./Input.h"
#include"./Window.h"
#include"./Timer.h"
#include"./RenderContext.h"
#include"./OpenGLContext.h"
#include"../../shader/ShaderClass.h"
#include"../../vertex/VAO.h"
#include"../../vertex/VBO.h"
#include"../../vertex/EBO.h"