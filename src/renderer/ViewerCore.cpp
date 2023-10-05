#include "ViewerCore.h"
using namespace renderer;

void ViewerCore::setup(config::Viewer&& viewer_configuration)
{
    options->sharedObjects = vsg::SharedObjects::create();

    auto shaderSet = vsg::createFlatShadedShaderSet(options);
    auto graphicsPipelineConfig = vsg::GraphicsPipelineConfigurator::create(shaderSet);
    graphicsPipelineConfig->init();

    vsg::ref_ptr<vsg::Window> window(vsg::Window::create(vsg::WindowTraits::create()));
    if (!window)
    {
        throw std::runtime_error("Failed to initialize the window");
    }
    window->clearColor() = VkClearColorValue{{0.32, 0.05, 0.05, 1}};

    viewer->addWindow(window);
    // set up the camera
    float radius = 233; //> to encompass currently used correct physical solar-systems scales
    auto  lookAt = vsg::LookAt::create(vsg::dvec3(0.0, -radius * 3.5, 0.0), vsg::dvec3(), vsg::dvec3(0.0, 0.0, 1.0));
    auto  perspective = vsg::Perspective::create(30.0,
                                                static_cast<double>(window->extent2D().width) /
                                                    static_cast<double>(window->extent2D().height),
                                                /*nearfar ratio*/ 0.01,
                                                1000);
    camera = vsg::Camera::create(perspective, lookAt, vsg::ViewportState::create(window->extent2D()));
#if STAGE_1
    updater = DirectUpdater::create(sceneRoot, viewer, camera, reg); // SceneUpdater::create(sceneRoot, viewer, queue);
    viewer->addEventHandler(updater);
#endif
    auto commandGraph = vsg::CommandGraph::create(window);
    auto renderGraph = vsg::RenderGraph::create(window);
    commandGraph->addChild(renderGraph);

    // create the normal 3D view of the scene
    auto view = vsg::View::create(camera);
    view->addChild(vsg::createHeadlight());
    view->addChild(sceneRoot);

    renderGraph->addChild(view);
#if STAGE_1
    {
        auto renderImGui = vsgImGui::RenderImGui::create(window, OrbitEditorGui::create(reg));
        renderGraph->addChild(renderImGui);
        // Add the ImGui event handler first to handle events early
        viewer->addEventHandler(vsgImGui::SendEventsToImGui::create());
    }
#endif
    viewer->addEventHandler(vsg::CloseHandler::create(viewer));
    viewer->assignRecordAndSubmitTaskAndPresentation({commandGraph});
    viewer->compile();
}

bool ViewerCore::frame()
{
    if (firstFrame)
    {
        firstFrame = false;
    }

    const auto advance = viewer->advanceToNextFrame();
    if (advance)
    {
        // pass any events into EventHandlers assigned to the Viewer
        viewer->handleEvents();

        viewer->update();

        viewer->recordAndSubmit();

        viewer->present();
    }
    return advance;
}

vsg::ref_ptr<vsg::Camera> ViewerCore::getCamera()
{
    return camera;
}

vsg::ref_ptr<vsg::Viewer> ViewerCore::getViewer() 
{
    return viewer;
}

vsg::ref_ptr<vsg::Group> ViewerCore::getSceneRoot()
{
    return sceneRoot;
}
