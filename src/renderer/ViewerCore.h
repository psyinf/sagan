#pragma once
#include <entt/entt.hpp>
#include <functional>
#include <vsg/all.h>
#include "ViewerConfig.h"

namespace renderer {

class ViewerCore
{
public:
    void setup(config::Viewer&& viewer_configuration = {});

    bool frame();

    vsg::ref_ptr<vsg::Camera> getCamera();

    vsg::ref_ptr<vsg::Viewer> getViewer();

    vsg::ref_ptr<vsg::Group> getSceneRoot();

private:
    vsg::ref_ptr<vsg::Viewer>          viewer = vsg::Viewer::create();
    vsg::ref_ptr<vsg::Options>         options = vsg::Options::create();
    vsg::ref_ptr<vsg::MatrixTransform> sceneRoot = vsg::MatrixTransform::create();
    vsg::ref_ptr<vsg::Visitor>         updater;

    vsg::ref_ptr<vsg::Camera> camera;
    bool                      firstFrame = true;
};
} // namespace renderer 
