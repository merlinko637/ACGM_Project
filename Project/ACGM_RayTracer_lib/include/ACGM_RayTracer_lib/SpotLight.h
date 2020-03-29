#pragma once
#include <ACGM_RayTracer_lib/PointLight.h>

namespace acgm 
{
	class SpotLight :
		public PointLight
	{
	public:
		explicit SpotLight(float intensity, const glm::vec3 position,
			const float range, const float linearAttFact, const float quadraticAttFact,
			const glm::vec3 coneDirection, const float cutoffAngle,
			const float exponent);
		virtual ~SpotLight() = default;

		glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
		float GetIntensityAt(const glm::vec3& point) const override;
		float GetDistanceFromLight(const glm::vec3& point) const override;

	private:
		const glm::vec3 coneDirection_;
		const float cutoffAngle_;
		const float exponent_;
	};
}