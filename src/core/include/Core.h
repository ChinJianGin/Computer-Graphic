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


// GLM
#define GLM_EXT_INCLUDED
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>

#define BIT(x) (1 << x)

#define BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace CustomSpace
{
    struct Transform
    {
        glm::mat4 m_ModelMatrix;
        glm::vec3 m_Position;
        glm::vec3 m_Axis;
        glm::vec3 m_Scale;
        float m_Rotation;

        bool IsAChild;
        glm::mat4 m_FatherTranslate;

        Transform(const glm::vec3& pos = glm::vec3(0), float rotation = 0, const glm::vec3& axis = glm::vec3(0, 0, 1), glm::vec3 scale = glm::vec3(1, 1, 1), bool child = false)
        : m_Position(pos), m_Rotation(rotation), m_Axis(axis), m_Scale(scale), IsAChild(child)
        {
            m_ModelMatrix = glm::translate(glm::mat4(1.f), pos)
             * glm::rotate(glm::mat4(1.f), m_Rotation, m_Axis)
             * glm::scale(glm::mat4(1.f), glm::vec3(m_Scale.x, m_Scale.y, m_Scale.z));
        }
    };

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
//#include"vector2.hpp"
//#include"vector3.hpp"
#include"./Log.h"
// #include"./LinkList.h"
#include"./LinkedList.h"
#include"./Input.h"
#include"./Window.h"
#include"./Timer.h"
#include"../../shader/ShaderClass.h"
#include"./OrthoCamera.h"