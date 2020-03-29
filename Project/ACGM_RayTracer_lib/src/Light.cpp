#include <ACGM_RayTracer_lib/Light.h>


acgm::Light::Light(float intensity) : intensity_(intensity)
{

}

const float acgm::Light::GetIntensity()
{
	return intensity_;
}

glm::vec3 acgm::Light::GetDirectionToLight(const glm::vec3& point) const
{
	return point;
}

float acgm::Light::GetIntensityAt(const glm::vec3& point) const
{
	return intensity_;
}

float acgm::Light::GetDistanceFromLight(const glm::vec3& point) const
{
	return INFINITY;
}