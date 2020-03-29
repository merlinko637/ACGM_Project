#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>
#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
    class Scene
    {
    public:
        Scene(std::shared_ptr<acgm::Camera> cam, 
            std::vector<std::shared_ptr<acgm::Model>> models, 
            std::shared_ptr<acgm::Light> light);
        ~Scene() = default;

        void Raytrace(hiro::draw::PRasterRenderer &renderer) const;

    private:
        std::shared_ptr<acgm::Camera> camera_;
        std::vector<std::shared_ptr<acgm::Model>> models_;
        std::shared_ptr<acgm::Light> light_;
    };
}
