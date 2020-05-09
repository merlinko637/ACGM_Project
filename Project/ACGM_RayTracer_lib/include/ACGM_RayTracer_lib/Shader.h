#pragma once

#include <COGS/Color.h>

namespace acgm 
{
	struct ShaderInput
	{
		glm::vec3 point;
		glm::vec3 normal;
		glm::vec3 directionToEye;
		glm::vec3 directionToLight;
		float lightIntensity;
		bool isPointInShadow;
	};

	struct ShaderOutput
	{
		cogs::Color3f color;
		float glossiness;
		float transparency;
		float refractiveIndex;
	};

	class Shader
	{
	public:
		explicit Shader(cogs::Color3f color);
		virtual ~Shader() = default;
		Shader();
		
		//calculates color for given ShaderInput
		virtual ShaderOutput CalculateColor(const ShaderInput& input) const = 0;
	protected:
		const cogs::Color3f color_;
	};
}