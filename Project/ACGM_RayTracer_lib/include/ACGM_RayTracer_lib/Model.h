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
    
        //computes intersection between given ray and model
        virtual std::optional<acgm::HitResult> ComputeIntersection(std::shared_ptr<acgm::Ray> ray) = 0;

        //sets given shader to model
        void SetShader(std::shared_ptr<acgm::Shader> shader);

        //returns shader of this model
        std::shared_ptr<acgm::Shader> GetShader();

        std::string name;
    private:
        std::shared_ptr<acgm::Shader> shader_;
    };
}
