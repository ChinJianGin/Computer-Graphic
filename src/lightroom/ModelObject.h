#pragma once
#include"../core/include/Core.h"
#include"../physics/Transform.h"
#include"../graphic/ModelLoad/Model.h"

namespace CustomSpace
{
    class ModelObject
    {
        public:
        ModelObject(const char* path);

        ~ModelObject();

        void Init(const char* path);

        void Update(Shader& shader);
        void UpdateWithNormal(Shader& shader, bool normal = false);

        Ref<Transform>& GetTransform() { return this->m_Transform; }
        void SetModelMatrix(glm::mat4& model);
        void SetPosition(glm::vec3& pos);
        void SetRotation(float radians, glm::vec3& axis);
        void SetScale(glm::vec3& scale);
        void SetParent(Ref<Transform>& parent);
        protected:
        Ref<Transform> m_Transform;
        Ref<Model> m_Model;
    };
}