#pragma once
#include <ACGM_RayTracer_lib/Light.h>

namespace acgm
{
	class PointLight : public Light
	{
	public:
		explicit PointLight(float intensity, const glm::vec3 position,
			const float range, const float linearAttFact, const float quadraticAttFact);
		virtual ~PointLight() = default;

		//returns direction from given point to light
		glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;

		//returns light intensity at given point
		float GetIntensityAt(const glm::vec3& point) const override;

		//returns distance from given point to light
		float GetDistanceFromLight(const glm::vec3& point) const override;

	private:
		const glm::vec3 position_;
		const float range_;
		const float linearAttenuationFactor_;
		const float quadraticAttenuationFactor_;
	};
}