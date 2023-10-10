#pragma once
#include <JsonSerializer.h>

namespace renderer::config {

struct NearFar
{
    double near{0.1};
    double far{1e5};
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(NearFar, near, far);
};

struct Viewer
{
    NearFar   nearFar;
    vsg::vec4 clearColor{0.0, 0.0, 0.0, 1.0};
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Viewer, nearFar, clearColor);
};
} // namespace renderer::config
