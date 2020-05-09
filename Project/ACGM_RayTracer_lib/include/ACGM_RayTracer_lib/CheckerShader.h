#pragma once

#include <ACGM_RayTracer_lib/Shader.h>

namespace acgm
{
	class CheckerShader : public Shader
	{
	public:
		explicit CheckerShader(float cubeSize, 
			const std::shared_ptr<Shader> shader1, const std::shared_ptr<Shader> shader2);

		//calculates color for given ShaderInput
		ShaderOutput CalculateColor(const ShaderInput& input) const override;

	private:
		const float cubeSize_;
		std::shared_ptr<Shader> shader1_;
		std::shared_ptr<Shader> shader2_;
	};
}


