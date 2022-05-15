#pragma once

//#define USING_VSYNC
//#define DISPLAY_FPS

#ifndef USING_VSYNC
    #define VSYNC false
    #define TARGET_FRAMERATE 60
#else
    #define VSYNC true
    #define TARGET_FRAMERATE 60
#endif

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
#include<cstdlib>
#include<ctime>


// GLM
#define GLM_EXT_INCLUDED
#define GLM_ENABLE_EXPERIMENTAL
#define GLM_GTX_quaternion
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/quaternion.hpp>

#define BIT(x) (1 << x)

#define BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace CustomSpace
{
    struct PointsData
    {
        std::vector<GLfloat> Points;
    };

    

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
#include"./Log.h"
#include"./LinkedList.h"
#include"./Input.h"
#include"./Window.h"
#include"./Timer.h"
#include"../../shader/ShaderClass.h"
#include"./OrthoCamera.h"
#include"./PerspectiveCamera.h"