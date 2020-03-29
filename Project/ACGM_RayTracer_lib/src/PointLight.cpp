#include <ACGM_RayTracer_lib/PointLight.h>
#include <iostream>

acgm::PointLight::PointLight(float intensity, const glm::vec3 position,
	const float range, const float linearAttFact, const float quadraticAttFact) :
	Light(intensity), position_(position), range_(range),
	linearAttenuationFactor_(linearAttFact), quadraticAttenuationFactor_(quadraticAttFact)
{

}

glm::vec3 acgm::PointLight::GetDirectionToLight(const glm::vec3& point) const
{
	return position_ - point;
}

float acgm::PointLight::GetIntensityAt(const glm::vec3& point) const
{
	float distance = glm::distance(position_, point);
	float linearAttenuation = range_ / (range_ + distance * linearAttenuationFactor_);
	float rangePow2 = pow(range_, 2);
	float distPow2 = pow(distance, 2);
	float quadraticAttenuation = rangePow2 / (rangePow2 + distPow2 * quadraticAttenuationFactor_);
	float finalIntensity = linearAttenuation * quadraticAttenuation * intensity_;
	
	return finalIntensity;
}

float acgm::PointLight::GetDistanceFromLight(const glm::vec3& point) const
{
	return glm::distance(position_, point);
}