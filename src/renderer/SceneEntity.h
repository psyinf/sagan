#pragma once
#include <vsg/core/Inherit.h>
#include <vsg/maths/mat4.h>
#include <vsg/maths/transform.h>
#include <vsg/maths/vec3.h>
#include <vsg/maths/vec4.h>
#include <vsg/nodes/MatrixTransform.h>

namespace renderer {

class SceneEntity : public vsg::Inherit<vsg::MatrixTransform, SceneEntity>
{
    void setPosition(const vsg::dvec3& position) { this->position = position; };

    const vsg::dvec3& getPostion() const { return position; }

    void update() 
    {
        this->matrix = vsg::translate(position) * vsg::rotate(vsg::dquat{}) *
                       vsg::scale(scale); // pivot* vsg::translate(- vsg::dvec3{0,0,-0});
    }

private:
    vsg::dvec3 position{};
    vsg::dquat rotation{};
    vsg::dvec3 scale{};
};
} // namespace renderer