#include <ACGM_RayTracer_lib/DirectionalLight.h>

acgm::DirectionalLight::DirectionalLight(const float intensity, const glm::vec3 direction) 
	: Light(intensity), direction_(direction)
{

}

glm::vec3 acgm::DirectionalLight::GetDirectionToLight(const glm::vec3& point) const
{
	return -direction_;
}

float acgm::DirectionalLight::GetIntensityAt(const glm::vec3& point) const
{
	return intensity_;
}

float acgm::DirectionalLight::GetDistanceFromLight(const glm::vec3& point) const
{
	return INFINITY;
}