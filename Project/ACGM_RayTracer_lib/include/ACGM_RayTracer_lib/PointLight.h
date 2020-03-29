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

		glm::vec3 GetDirectionToLight(const glm::vec3& point) const override;
		float GetIntensityAt(const glm::vec3& point) const override;
		float GetDistanceFromLight(const glm::vec3& point) const override;

	private:
		const glm::vec3 position_;
		const float range_;
		const float linearAttenuationFactor_;
		const float quadraticAttenuationFactor_;
	};
}