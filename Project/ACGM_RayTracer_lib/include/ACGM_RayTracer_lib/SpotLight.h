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

		//returns direction to light from given point
		glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;

		//returns light intensity at given point
		float GetIntensityAt(const glm::vec3& point) const override;

		//returns distance from given point to light
		float GetDistanceFromLight(const glm::vec3& point) const override;

	private:
		const glm::vec3 coneDirection_;
		const float cutoffAngle_;
		const float exponent_;
	};
}