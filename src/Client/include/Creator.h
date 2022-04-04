#pragma once

#include"../../graphic/Shape.h"

namespace CustomSpace
{
    class ShapeFactory
    {
        public:
            ShapeFactory();

            template<typename T = Shape>
            Ref<T> ShapeCreator();

        private:

            static void CalculateIndices(Shape::ShapeType type, std::vector<GLuint>& indices);
    };

    inline void ShapeFactory::CalculateIndices(Shape::ShapeType type, std::vector<GLuint>& indices)
    {
        std::vector<GLuint> Indices;
        switch (type)
        {
        case Shape::ShapeType::None:
            CORE_WARN("Not set shape type.");
            break;
        case Shape::ShapeType::Point:
            Indices[0] = 0;
            break;
        case Shape::ShapeType::Line:
            Indices[0] = 0;
            Indices[1] = 1;
            break;
        case Shape::ShapeType::Sphere:

            break;
        case Shape::ShapeType::Triangle:
            Indices[0] = 0;
            Indices[1] = 1;
            Indices[2] = 2;
            break;
        case Shape::ShapeType::Quad:
            Indices[0] = 0;
            Indices[1] = 1;
            Indices[2] = 2;
            Indices[3] = 1;
            Indices[4] = 2;
            Indices[5] = 3;
            break;
        default:
            break;
        }
        indices = Indices;
    }
}