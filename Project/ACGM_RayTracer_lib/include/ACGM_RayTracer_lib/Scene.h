#pragma once

#include <vector>
#include <HIRO_DRAW/renderers/RasterRenderer.h>
#include <ACGM_RayTracer_lib/Camera.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Light.h>
#include <ACGM_RayTracer_lib\Image.h>

namespace acgm
{
    class Scene
    {
    public:
        Scene(std::shared_ptr<acgm::Camera> cam, 
            std::vector<std::shared_ptr<acgm::Model>> models, 
            std::shared_ptr<acgm::Light> light,
            const float bias, const float indexOfRefraction,
            const glm::vec3 enviroUp, const glm::vec3 enviroSeam,
            std::string imageFilePath);
        ~Scene() = default;

        void Raytrace(hiro::draw::PRasterRenderer &renderer) const;

    private:
        cogs::Color3f CalculatePixelColor(std::shared_ptr<acgm::Ray> ray,
            int maxReflectionDepth, int maxTransparencyDepth) const;
        cogs::Color3f NoObjectHit(glm::vec3 direction) const;

        std::shared_ptr<acgm::Camera> camera_;
        std::vector<std::shared_ptr<acgm::Model>> models_;
        std::shared_ptr<acgm::Light> light_;
        std::shared_ptr<acgm::Image> image_;

        const float bias_;
        const float refractiveIndex_;
        const glm::vec3 enviroUp_;
        const glm::vec3 enviroSeam_;
    };
}
