#include <ACGM_RayTracer_lib/Plane.h>
#include <glm/geometric.hpp>

acgm::Plane::Plane(const glm::vec3& point, const glm::vec3& normal)
	: point_(point), normal_(normal)
{

}

std::optional<acgm::HitResult> acgm::Plane::ComputeIntersection(std::shared_ptr<acgm::Ray> ray)
{
	auto denominator = glm::dot(ray->GetDirection(), normal_);

	if (denominator == 0)
	{
		return std::nullopt;
	}

	glm::vec3 tmp1 = point_ - ray->GetOrigin();
	float t = glm::dot(tmp1, normal_) / denominator;

	HitResult hit;

	hit.rayParam = t;
	hit.normal = normal_;
	hit.point = ray->GetPoint(t);

	return hit;
}