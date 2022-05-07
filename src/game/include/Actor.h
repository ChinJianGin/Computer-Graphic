#pragma once
#include"../../core/include/Core.h"
#include "../../core/include/Timer.h"
#include"../../graphic/Renderer.h"
#include"../../client/include/Creator.h"
#include"../../graphic/Texture.h"

namespace CustomSpace
{
    class Actor
    {
        public:
        virtual void Init(const Ref<ShapeFactory>& fctory) = 0;
        virtual void Update(const CoreTimer& timer) = 0;
        
        virtual void SetTransform(const Ref<Transform>& trans) = 0;
        virtual void SetPosition(const glm::vec3& pos) = 0;
        virtual void SetPosition(const float pos, int axis) = 0;
        virtual void SetColor(const std::vector<glm::vec4> colors) = 0;
        virtual void SetRotation(const float rotation, const glm::vec3& axis = glm::vec3(0, 0, 1)) = 0;
        virtual void SetScale(const glm::vec3& scale) = 0;

        virtual Ref<Transform> GetTransform() const = 0;  
        virtual Ref<PointsData> GetPointsData() const = 0;
        virtual Ref<VertexData> GetVertexData() const = 0;   
        virtual Ref<BoundingObject> GetBounding() const = 0;

        virtual void ModelMatrixMethod(const Shape::MatrixMethod method = Shape::MatrixMethod::TRS) = 0;



        virtual void AttackAction() = 0;
        virtual void SetEnableActor(bool enable) { b_Enable = enable; }
        private:

        protected:

        Ref<Shape> m_Body;    
        bool b_Enable = false;
    
    };
}