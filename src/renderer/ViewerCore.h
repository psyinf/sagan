#pragma once
#include <entt/entt.hpp>
#include <functional>
#include <vsg/all.h>

class ViewerCore
{
public:
    void setup(/*entt::registry &reg*/);

    bool frame();

    vsg::ref_ptr<vsg::Camera> getCamera();

private:
    vsg::ref_ptr<vsg::Viewer>          viewer = vsg::Viewer::create();
    vsg::ref_ptr<vsg::Options>         options = vsg::Options::create();
    vsg::ref_ptr<vsg::MatrixTransform> sceneRoot = vsg::MatrixTransform::create();
    vsg::ref_ptr<vsg::Visitor>         updater;

    vsg::ref_ptr<vsg::Camera> camera;
    bool                      firstFrame = true;
};