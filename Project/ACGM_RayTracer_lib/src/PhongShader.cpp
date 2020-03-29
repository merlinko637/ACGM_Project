#include <ACGM_RayTracer_lib/PhongShader.h>
#include <glm\detail\func_geometric.hpp>

acgm::PhongShader::PhongShader(cogs::Color3f color, float shininess,
	float ambient, float diffuse, float specular) : Shader(color), shininess_(shininess),
	ambient_(ambient), diffuse_(diffuse), specular_(specular)
{

}

cogs::Color3f acgm::PhongShader::CalculateColor(const ShaderInput& input) const
{
    float cosAngle = glm::dot(input.normal, input.directionToLight);

    cogs::Color3f ambientPhong = color_ * ambient_ * cosAngle;

    if (input.isPointInShadow)
    {
        return ambientPhong;
    }

    cogs::Color3f diffusePhong = color_ * diffuse_ * input.lightIntensity * cosAngle;

    auto whiteColor = cogs::Color3f(1.0f, 1.0f, 1.0f);
    glm::vec3 halfVector = glm::normalize(input.directionToEye + input.directionToLight);
    cogs::Color3f specularPhong = whiteColor * specular_ * input.lightIntensity * pow(glm::dot(halfVector, input.normal), shininess_);

    return ambientPhong + diffusePhong + specularPhong;
}