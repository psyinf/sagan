#pragma once
#include "LoadOperation.h"
#include "SceneEntity.h"
#include <vsg/all.h>

namespace renderer {

class SceneFactory : public vsg::Inherit<vsg::Visitor, SceneFactory>
{
    static const auto num_threads = 1u;

public:
    SceneFactory(vsg::ref_ptr<vsg::Viewer> viewer)
      : viewer(viewer)
      , threads(vsg::OperationThreads::create(num_threads, viewer->status))
    {
    }

    /**
     * \brief Make a 
     */
    auto makeSceneEntity(vsg::ref_ptr<vsg::Node> node) -> vsg::ref_ptr<SceneEntity>
    {
        auto new_object = SceneEntity::create();
        threads->add(CompileOperation::create(viewer, new_object, node));
        return new_object;
    }

    vsg::ref_ptr<vsg::Builder> getBuilder() { return builder; }

private:
    vsg::observer_ptr<vsg::Viewer>      viewer;
    vsg::ref_ptr<vsg::OperationThreads> threads;
    vsg::ref_ptr<vsg::Builder>          builder = vsg::Builder::create();  
};

} // namespace renderer