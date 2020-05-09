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

        //returns camera position
        glm::vec3 GetPosition() const;

        //returns view direction of camera
        glm::vec3 ForwardDirection() const;

        //returns up vector of camera
        glm::vec3 UpDirection() const;

        //returns field of view of camera
        float GetFieldOfView() const;


    private:
        const glm::vec3 position_;
        const glm::vec3 forwardDirection_;
        const glm::vec3 upDirection_;
        const float fieldOfView_;
    };
}
