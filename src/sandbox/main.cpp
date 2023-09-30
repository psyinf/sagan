#include "SceneEntity.h"
#include "SceneFactory.h"
#include "ViewerCore.h"

int main(int argc, char** argv)
{
    renderer::ViewerCore viewerCore;
    viewerCore.setup();

    renderer::SceneFactory sceneFactory{viewerCore.getViewer()};
    vsg::GeometryInfo      geom_info;
    geom_info.position = {1, 1, 1};

    viewerCore.getViewer()->addEventHandler(vsg::Trackball::create(viewerCore.getCamera()));
    auto node = sceneFactory.getBuilder()->createBox(geom_info);
    viewerCore.getSceneRoot()->addChild(sceneFactory.makeSceneEntity(node));
    while (viewerCore.frame())
    {
    }
    return 0;
}