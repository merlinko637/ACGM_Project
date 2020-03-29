#pragma once
#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
	class PhongShader : public Shader
	{
	public:
		explicit PhongShader(cogs::Color3f color, float shininess,
			float ambient, float diffuse, float specular);

		cogs::Color3f CalculateColor(const ShaderInput& input) const override;

	private:
		const float shininess_;
		const float ambient_;
		const float diffuse_;
		const float specular_;
	};
}

