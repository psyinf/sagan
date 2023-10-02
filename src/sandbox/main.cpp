#include "SceneEntity.h"
#include "SceneFactory.h"
#include "ViewerCore.h"
#include "yaml-cpp/yaml.h"

int main(int argc, char** argv)
{
    renderer::ViewerCore viewerCore;
    viewerCore.setup();

    YAML::Node config = YAML::LoadFile("data/config/viewer.yaml");

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