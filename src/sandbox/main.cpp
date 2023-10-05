#include "ViewerConfig.h"
#include "SceneEntity.h"
#include "SceneFactory.h"
#include "ViewerCore.h"
#include <iostream>
#include "ErrorTrace.h"
#include "YamlJson.h"

int main(int argc, char** argv)
try
{
    auto                 nf2 = config::load<renderer::config::Viewer>("data/config/viewer.yaml");

    renderer::ViewerCore viewerCore;

    viewerCore.setup();
    //auto                   nf2 = config::load<config::Viewer>("data/config/viewer.json");
    //auto                   nf = config::load<config::Viewer>("data/config/viewer.yaml");
    renderer::SceneFactory sceneFactory{viewerCore.getViewer()};
    vsg::GeometryInfo      geom_info;
    geom_info.position = {1, 1, 1};

    viewerCore.getViewer()->addEventHandler(vsg::Trackball::create(viewerCore.getCamera()));
    auto node = sceneFactory.getBuilder()->createBox(geom_info);
    viewerCore.getSceneRoot()->addChild(sceneFactory.makeSceneEntity(node));
    while (viewerCore.frame()) {}
    return 0;
}
catch (const std::exception& e)
{
    std::cerr << e.what() << std::endl;
    errorTrace::printErrorTrace();
}