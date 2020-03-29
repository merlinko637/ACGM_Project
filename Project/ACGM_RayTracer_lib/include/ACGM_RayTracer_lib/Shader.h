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

	class Shader
	{
	public:
		explicit Shader(cogs::Color3f color);
		virtual ~Shader() = default;
		Shader();
		
		virtual cogs::Color3f CalculateColor(const ShaderInput& input) const;
	protected:
		const cogs::Color3f color_;
	};
}