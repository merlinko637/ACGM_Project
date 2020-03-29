#pragma once

#include <glm/glm.hpp>

namespace acgm {

	class Light
	{
	public:
		explicit Light(float intensity);
		virtual ~Light() = default;

		const float GetIntensity();

		virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const;
		virtual float GetIntensityAt(const glm::vec3& point) const;
		virtual float GetDistanceFromLight(const glm::vec3& point) const;

	protected:
		const float intensity_;
	};

}


