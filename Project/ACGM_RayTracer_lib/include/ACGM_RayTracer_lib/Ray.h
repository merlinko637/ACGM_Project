#pragma once

#include <glm/vec3.hpp>

namespace acgm
{
    class Ray
    {
    public:
        Ray(const glm::vec3 origin, const glm::vec3 direction, const float bias);

        glm::vec3 GetOrigin() const;
        glm::vec3 GetDirection() const;
        glm::vec3 GetPoint(const float t) const;
        glm::vec3 GetReflectionDirection(const glm::vec3 & normal) const;
        float GetBias() const;

    private:
        const glm::vec3 origin_;
        const glm::vec3 direction_;
        const float bias_;
    };
}
