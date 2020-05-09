#pragma once
#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
	class DirectionalLight : public Light
	{
	public:
		explicit DirectionalLight(const float intensity, const glm::vec3 direction);

		//returns direction to light from given point
		glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;

		//returns light intensity at given point
		float GetIntensityAt(const glm::vec3& point) const override;

		//returns distance from given point to light
		float GetDistanceFromLight(const glm::vec3& point) const override;

	private:
		const glm::vec3 direction_;
	};
}

