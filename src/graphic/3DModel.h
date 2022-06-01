#pragma once
#include"./Shape.h"

namespace CustomSpace
{
    class CustomModel : public Shape
    {
        public:
        virtual ~CustomModel() = default;

        virtual void CalTangentSpace(std::vector<GLfloat>& points)
        {
            int pointsNum = points.size() / 8;
            int trianglesNum = pointsNum / 3;
            int dataSize = points.size();
            CORE_INFO("Num : {0}", pointsNum);
            glm::vec3 pos[pointsNum];
            glm::vec2 uv[pointsNum];
            for(int i = 0; i < dataSize; i = i+8)
            {
                int _num = i / 8;
                pos[_num].x = points[i];
                pos[_num].y = points[i + 1];
                pos[_num].z = points[i + 2];

                uv[_num].x = points[i + 6];
                uv[_num].y = points[i + 7];
            }

            for(int i = 0; i < trianglesNum; i++)
            {
                glm::vec3 edge1 = pos[i * 3 + 1] - pos[i * 3];
                glm::vec3 edge2 = pos[i * 3 + 2] - pos[i * 3];

                glm::vec2 deltaUV1 = uv[i * 3 + 1] - uv[i * 3];
                glm::vec2 deltaUV2 = uv[i * 3 + 2] - uv[i * 3];

                float f = 1.f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
                glm::vec3 tangent1 = glm::vec3(f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
                                            f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
                                            f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z));

                glm::vec3 bitangent1 = glm::vec3(f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
                                                f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
                                                f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z));
                std::vector<GLfloat> insetVector = {
                    tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z
                };
                for(int j = 1; j <= 3; j++)
                {
                    int offset = (j * 8) + ((j - 1) * 6) + (i * 42);
                    points.insert(points.begin() + offset, insetVector.begin(), insetVector.end());
                }
            }
            // for(int j = 0; j < pointsNum; j++)
            // {
            //     CORE_TRACE("X : {0} , Y : {1} , Z : {2}", pos[j].x, pos[j].y, pos[j].z);
            //     CORE_TRACE("U : {0} , V : {1}", uv[j].x, uv[j].y);
            // }
        }
    };
}