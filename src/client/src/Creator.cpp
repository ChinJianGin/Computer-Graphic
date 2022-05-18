#include "../include/Creator.h"


namespace CustomSpace
{
    ShapeFactory* ShapeFactory::Instance = nullptr;

    ShapeFactory::ShapeFactory()
    {
        CORE_WARN("Create Factory");
        Instance = this;
    }
}