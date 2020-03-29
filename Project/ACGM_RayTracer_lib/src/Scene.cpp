#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib\Mesh.h>

#include <omp.h>


acgm::Scene::Scene(std::shared_ptr<acgm::Camera> cam, 
    std::vector<std::shared_ptr<acgm::Model>> models, 
    std::shared_ptr<acgm::Light> light)
    : camera_(cam), models_(models), light_(light)
{

}

void acgm::Scene::Raytrace(hiro::draw::PRasterRenderer &renderer) const
{
    glm::uint width = renderer->GetResolution().x;
    glm::uint height = renderer->GetResolution().y;

    glm::vec3 v = camera_->UpDirection();
    glm::vec3 u = camera_->ForwardDirection();
    glm::vec3 w = glm::cross(u, v); 

    float fov = camera_->GetFieldOfView();
    float fovRad = glm::radians(fov);
    float y = tan(fovRad / 2.);
    float x = -y;

    float dy = 2.0f * tan(fovRad / 2.0f) / (float)height;
    float dx = 2.0f * tan(fovRad / 2.0f) / (float)width;

    float bias = 0.001f;

    float light_energy = 2.0f;

    int pixelY, pixelX, k;

    for (pixelY = height - 1; pixelY >= 0; pixelY--)
    {
        for (pixelX = 0; pixelX < width; pixelX++)
        {
            glm::vec3 dir = glm::normalize(u + x * w + y * v);

            auto ray = std::make_shared<acgm::Ray>(camera_->GetPosition(), dir, bias);

            bool pixelSet = false;
            int minIndex = 0;
            std::optional<HitResult> hitResult;
            HitResult minHitResult;
            minHitResult.rayParam = INFINITY;
            
            for (k = 0; k < models_.size(); k++)
            {
                std::shared_ptr<acgm::Model> model = models_.at(k);
                hitResult = model->ComputeIntersection(ray);

                if (hitResult == std::nullopt)
                {
                    continue;
                }

                if (hitResult.value().rayParam >= 0 && hitResult.value().rayParam < minHitResult.rayParam)
                {
                    minIndex = k;
                    minHitResult = hitResult.value();
                    pixelSet = true;
                }
            }

            if (!pixelSet)
            {
                renderer->SetPixel(pixelX, pixelY, cogs::Color3f(0, 0, 0));
                pixelSet = false;
            }
            else
            {
                

                HitResult minShadowHitResult;
                minShadowHitResult.rayParam = INFINITY;

                auto point = minHitResult.point;
                bool isInShadow = false;
                auto directionToLight = glm::normalize(light_->GetDirectionToLight(point));
                auto shadowRay = std::make_shared<acgm::Ray>(point + minHitResult.normal * bias, directionToLight, bias);
                auto distanceToLight = light_->GetDistanceFromLight(point);
                for (int m = 0; m < models_.size(); m++)
                {
                    auto shadowModel = models_.at(m);
                    auto shadowHit = shadowModel->ComputeIntersection(shadowRay);

                    if (shadowHit == std::nullopt)
                    {
                        continue;
                    }

                    if (shadowHit.value().rayParam > 0 && shadowHit.value().rayParam < distanceToLight)
                    {
                        isInShadow = true;
                        break;
                    }
                }

                ShaderInput shaderInput;
                shaderInput.directionToLight = directionToLight;
                shaderInput.normal = glm::normalize(minHitResult.normal);
                shaderInput.point = point;
                shaderInput.directionToEye = glm::normalize(camera_->GetPosition() - point);
                shaderInput.lightIntensity = light_->GetIntensityAt(point);
                shaderInput.isPointInShadow = isInShadow;

                float ambient = 0.5f;
                float intensity = isInShadow ? ambient : ambient + (1 - ambient) * light_->GetIntensityAt(point);

                //renderer->SetPixel(pixelX, pixelY, models_.at(minIndex)->Color() * intensity);
                renderer->SetPixel(pixelX, pixelY, models_.at(minIndex)->GetShader()->CalculateColor(shaderInput));
            }

            x += dx;
        }
        y -= dy;
        x = -tan(fovRad / 2.);
    }
}
