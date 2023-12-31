#pragma once
#include <vsg/all.h>

struct MergeOperation : public vsg::Inherit<vsg::Operation, MergeOperation>
{
    MergeOperation(vsg::observer_ptr<vsg::Viewer> in_viewer,
                   vsg::ref_ptr<vsg::Group>       in_attachmentPoint,
                   vsg::ref_ptr<vsg::Node>        in_node)
      : viewer(in_viewer)
      , attachmentPoint(in_attachmentPoint)
      , node(in_node)
    {
    }

    vsg::observer_ptr<vsg::Viewer> viewer;
    vsg::ref_ptr<vsg::Group>       attachmentPoint;
    vsg::ref_ptr<vsg::Node>        node;
    vsg::CompileResult             compileResult;

    void run() override
    {
        if (vsg::ref_ptr<vsg::Viewer> ref_viewer = viewer; ref_viewer)
        {
            updateViewer(*ref_viewer, compileResult);
        }
        attachmentPoint->addChild(node);
    }
};

struct CompileOperation : public vsg::Inherit<vsg::Operation, CompileOperation>
{
    CompileOperation(vsg::ref_ptr<vsg::Viewer> in_viewer,
                     vsg::ref_ptr<vsg::Group>  in_attachmentPoint,
                     vsg::ref_ptr<vsg::Node>   node)
      : viewer(in_viewer)
      , attachment_point(in_attachmentPoint)
      , node(node)
    {
    }

    vsg::observer_ptr<vsg::Viewer> viewer;
    vsg::ref_ptr<vsg::Group>       attachment_point;
    vsg::ref_ptr<vsg::Node>        node;

    void run() override
    {
        vsg::ref_ptr<vsg::Viewer> ref_viewer = viewer;
        auto                      result = ref_viewer->compileManager->compile(node);
        if (result)
            ref_viewer->addUpdateOperation(MergeOperation::create(viewer, attachment_point, node));
    }
};
