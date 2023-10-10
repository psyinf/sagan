#pragma once
#include <vsg/maths/vec3.h>
#include <vsg/maths/vec4.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace vsg {
template <typename T>
inline void to_json(json& j, const t_vec3<T>& p)
{
    j = json::array();
    j.push_back(p[0]);
    j.push_back(p[1]);
    j.push_back(p[2]);
}

template <typename T>
inline void from_json(const json& j, t_vec3<T>& p)
{
    j[0].get_to(p[0]);
    j[1].get_to(p[1]);
    j[2].get_to(p[2]);
}

template <typename T>
inline void to_json(json& j, const t_vec4<T>& p)
{
    j = json::array();
    j.push_back(p[0]);
    j.push_back(p[1]);
    j.push_back(p[2]);
    j.push_back(p[3]);
}

template <typename T>
inline void from_json(const json& j, t_vec4<T>& p)
{
    j[0].get_to(p[0]);
    j[1].get_to(p[1]);
    j[2].get_to(p[2]);
    j[2].get_to(p[3]);
}
} // namespace vsg
