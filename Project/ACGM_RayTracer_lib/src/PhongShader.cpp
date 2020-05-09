#include <ACGM_RayTracer_lib/PhongShader.h>
#include <glm\detail\func_geometric.hpp>

acgm::PhongShader::PhongShader(cogs::Color3f color, float shininess,
	float ambient, float diffuse, float specular,
    float glossiness, float transparency, float refractiveIndex) : Shader(color), shininess_(shininess),
	ambient_(ambient), diffuse_(diffuse), specular_(specular), glossiness_(glossiness), 
    transparency_(transparency), refractiveIndex_(refractiveIndex)
{

}

acgm::ShaderOutput acgm::PhongShader::CalculateColor(const ShaderInput& input) const
{
    ShaderOutput output;
    output.glossiness = glossiness_;
    output.transparency = transparency_;
    output.refractiveIndex = refractiveIndex_;

    float cosAngle = glm::dot(input.normal, input.directionToLight);

    cogs::Color3f ambientPhong = color_ * ambient_ * cosAngle;

    if (input.isPointInShadow)
    {
        output.color = ambientPhong;
        return output;
    }

    cogs::Color3f diffusePhong = color_ * diffuse_ * input.lightIntensity * cosAngle;

    auto whiteColor = cogs::Color3f(1.0f, 1.0f, 1.0f);
    glm::vec3 halfVector = glm::normalize(input.directionToEye + input.directionToLight);
    cogs::Color3f specularPhong = whiteColor * specular_ * input.lightIntensity * pow(glm::dot(halfVector, input.normal), shininess_);

    output.color = ambientPhong + diffusePhong + specularPhong;
    return output;
}

