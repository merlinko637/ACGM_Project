#include <ACGM_RayTracer_lib/Shader.h>

acgm::Shader::Shader(cogs::Color3f color) : color_(color)
{

}

acgm::Shader::Shader()
{

}

acgm::ShaderOutput acgm::Shader::CalculateColor(const ShaderInput& input) const
{
	ShaderOutput output;
	return output;
}