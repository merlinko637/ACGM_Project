#pragma once
#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
	class DirectionalLight : public Light
	{
	public:
		explicit DirectionalLight(const float intensity, const glm::vec3 direction);

		glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
		float GetIntensityAt(const glm::vec3& point) const override;
		float GetDistanceFromLight(const glm::vec3& point) const override;

	private:
		const glm::vec3 direction_;
	};
}

