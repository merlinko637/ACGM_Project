#include <ACGM_RayTracer_lib/Ray.h>
#include <glm/geometric.hpp>


acgm::Ray::Ray(const glm::vec3 origin, const glm::vec3 direction, const float bias) 
	: origin_(origin), direction_(direction), bias_(bias)
{

}

glm::vec3 acgm::Ray::GetOrigin() const
{
	return origin_;
}

glm::vec3 acgm::Ray::GetDirection() const
{
	return direction_;
}

glm::vec3 acgm::Ray::GetPoint(const float t) const
{
	return origin_ + (t * direction_);
}

glm::vec3 acgm::Ray::GetReflectionDirection(const glm::vec3& normal) const
{
	float dot = glm::dot(direction_, normal);
	return -2 * dot * normal + direction_;
}

std::optional<glm::vec3> acgm::Ray::GetRefractionDirection(const float sourceIor, const float destIor, glm::vec3& normal) const
{
    float cosTheta1 = glm::dot(direction_, normal);
    float ior = glm::dot(normal, direction_) < 0 ? 
        sourceIor / destIor : destIor / sourceIor;

    if (cosTheta1 < 0)
    {
        cosTheta1 = -cosTheta1;
    }
    else
    {
        normal = -normal;
    }
    
    float iorPow2 = ior * ior;
    float cosTheta2Pow2 = 1 - iorPow2 * (1 - cosTheta1 * cosTheta1);

    if (cosTheta2Pow2 < 0)
    {
        return std::nullopt;
    }

    float cosTheta2 = std::sqrt(cosTheta2Pow2);
    return ior * direction_ + normal * (ior * cosTheta1 - cosTheta2);
}

float acgm::Ray::GetBias() const
{
	return bias_;
}