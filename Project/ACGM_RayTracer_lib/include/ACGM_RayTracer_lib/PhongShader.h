#pragma once
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
	class PhongShader : public Shader
	{
	public:
		explicit PhongShader(cogs::Color3f color, float shininess,
			float ambient, float diffuse, float specular,
			float glossiness, float transparency, float refractiveIndex);

		//calculates color for given ShaderInput object
		ShaderOutput CalculateColor(const ShaderInput& input) const override;


	private:
		const float shininess_;
		const float ambient_;
		const float diffuse_;
		const float specular_;
		const float glossiness_;
		const float transparency_;
		const float refractiveIndex_;
	};
}

