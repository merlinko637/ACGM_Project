#pragma once

#include <glm/vec3.hpp>
#include <optional>

namespace acgm
{
    class Ray
    {
    public:
        Ray(const glm::vec3 origin, const glm::vec3 direction, const float bias);

        //returns ray origin
        glm::vec3 GetOrigin() const;

        //returns ray direction
        glm::vec3 GetDirection() const;

        //returns point of intersection
        glm::vec3 GetPoint(const float t) const;

        //returns reflection direction for given normal
        glm::vec3 GetReflectionDirection(const glm::vec3 & normal) const;

        //returns refraction direction for given IORs and normal
        std::optional<glm::vec3> GetRefractionDirection(const float sourceIor, const float destIor, glm::vec3& normal) const;
        
        //returns bias of this ray
        float GetBias() const;

    private:
        const glm::vec3 origin_;
        const glm::vec3 direction_;
        const float bias_;
    };
}
