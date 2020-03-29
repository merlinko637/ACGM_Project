#pragma once

#include <ACGM_RayTracer_lib/Ray.h>

#include <optional>
#include <ACGM_RayTracer_lib\Shader.h>


namespace acgm
{
    struct HitResult {
        glm::vec3 normal;
        glm::vec3 point;
        float rayParam;
    };

    class Model
    {
    public:
        explicit Model();
        virtual ~Model() = default;
    
        virtual std::optional<acgm::HitResult> ComputeIntersection(std::shared_ptr<acgm::Ray> ray);

        void SetShader(std::shared_ptr<acgm::Shader> shader);
        std::shared_ptr<acgm::Shader> GetShader();

        std::string name;
    private:
        std::shared_ptr<acgm::Shader> shader_;
    };
}
