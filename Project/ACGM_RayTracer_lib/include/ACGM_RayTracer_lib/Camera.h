#pragma once

#include <glm/common.hpp>

namespace acgm
{
    class Camera
    {
    public:
        explicit Camera(const glm::vec3 &position,
            const glm::vec3 &forwardDirection,
            const glm::vec3& upDirection, float fov);

        glm::vec3 GetPosition() const;
        glm::vec3 ForwardDirection() const;
        glm::vec3 UpDirection() const;
        float GetFieldOfView() const;


    private:
        const glm::vec3 position_;
        const glm::vec3 forwardDirection_;
        const glm::vec3 upDirection_;
        const float fieldOfView_;
    };
}
