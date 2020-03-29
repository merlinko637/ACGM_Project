#include <ACGM_RayTracer_lib/Camera.h>

acgm::Camera::Camera(const glm::vec3& position,
    const glm::vec3& forwardDirection,
    const glm::vec3& upDirection, float fov)
    : position_(position), forwardDirection_(forwardDirection)
    , upDirection_(upDirection), fieldOfView_(fov)
{

}

glm::vec3 acgm::Camera::GetPosition() const
{
  return position_;
}

glm::vec3 acgm::Camera::ForwardDirection() const
{
    return forwardDirection_;
}

glm::vec3 acgm::Camera::UpDirection() const
{
    return upDirection_;
}

float acgm::Camera::GetFieldOfView() const
{
    return fieldOfView_;
}
