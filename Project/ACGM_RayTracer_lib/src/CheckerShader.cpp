#include <ACGM_RayTracer_lib/CheckerShader.h>

acgm::CheckerShader::CheckerShader(float cubeSize, const std::shared_ptr<Shader> shader1, const std::shared_ptr<Shader> shader2)
	: cubeSize_(cubeSize), shader1_(shader1), shader2_(shader2)
{

}

acgm::ShaderOutput acgm::CheckerShader::CalculateColor(const ShaderInput& input) const
{
	float bias = 0.001;

	auto x = floor((input.point.x / cubeSize_) + bias);
	auto y = floor((input.point.y / cubeSize_) + bias);
	auto z = floor((input.point.z / cubeSize_) + bias);

	int result = x + y + z;

	return result % 2 ? shader2_->CalculateColor(input) : shader1_->CalculateColor(input);
}