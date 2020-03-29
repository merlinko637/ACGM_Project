#include <ACGM_RayTracer_lib/SpotLight.h>
#include <glm/gtx/vector_angle.hpp>
#include <iostream>

acgm::SpotLight::SpotLight(float intensity, const glm::vec3 position,
	const float range, const float linearAttFact, const float quadraticAttFact,
	const glm::vec3 coneDirection, const float cutoffAngle,
	const float exponent) : PointLight(intensity, position, range, linearAttFact, quadraticAttFact),
	coneDirection_(coneDirection), cutoffAngle_(cutoffAngle), exponent_(exponent)
{

}

glm::vec3 acgm::SpotLight::GetDirectionToLight(const glm::vec3& point) const
{
	return acgm::PointLight::GetDirectionToLight(point);
}

float acgm::SpotLight::GetIntensityAt(const glm::vec3& point) const
{
	float point_intensity = acgm::PointLight::GetIntensityAt(point);
	glm::vec3 light_direction = glm::normalize(-GetDirectionToLight(point));

	float angle = glm::angle(coneDirection_, light_direction);
	angle = glm::degrees(angle);

	if (angle > cutoffAngle_) 
	{
		return 0.0f;
	}

	float decay = 1 - pow((angle / cutoffAngle_), exponent_);

	return point_intensity * decay;
}

float acgm::SpotLight::GetDistanceFromLight(const glm::vec3& point) const
{
	return acgm::PointLight::GetDistanceFromLight(point);
}