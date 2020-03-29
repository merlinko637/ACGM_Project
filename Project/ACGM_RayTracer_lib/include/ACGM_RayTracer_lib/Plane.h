#pragma once

#include <ACGM_RayTracer_lib/Model.h>

namespace acgm
{
  class Plane : public Model
  {
  public:
      explicit Plane(const glm::vec3 &point, const glm::vec3 &normal);
      virtual ~Plane() = default;

      std::optional<acgm::HitResult> ComputeIntersection(std::shared_ptr<acgm::Ray> ray) override;

  private:
      const glm::vec3 point_;
      const glm::vec3 normal_;
  };
}