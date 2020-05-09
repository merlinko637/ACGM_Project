#pragma once

#include <glm/glm.hpp>

namespace acgm {

	class Light
	{
	public:
		explicit Light(float intensity);
		virtual ~Light() = default;

		const float GetIntensity();

		//returns direction to light from given point
		virtual glm::vec3 GetDirectionToLight(const glm::vec3& point) const = 0;

		//returns light intensity at given point
		virtual float GetIntensityAt(const glm::vec3& point) const = 0;

		//returns distance from given point to light
		virtual float GetDistanceFromLight(const glm::vec3& point) const = 0;

	protected:
		const float intensity_;
	};

}


