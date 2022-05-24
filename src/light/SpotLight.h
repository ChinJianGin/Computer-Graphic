#pragma once
#include"./Light.h"

namespace CustomSpace
{
    class SpotLight : public Light
    {
        public:
            SpotLight();
            virtual ~SpotLight() = default;

            void Init() override;
    };
}