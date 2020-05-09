#include <ACGM_RayTracer_lib/Model.h>

acgm::Model::Model()
{
    
}

void acgm::Model::SetShader(std::shared_ptr<acgm::Shader> shader)
{
    shader_ = shader;
}

std::shared_ptr<acgm::Shader> acgm::Model::GetShader()
{
    return shader_;
}