#include <ACGM_RayTracer_lib/Scene.h>
#include <ACGM_RayTracer_lib/Plane.h>
#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib\Mesh.h>

#include <omp.h>
#include <glm\gtx\vector_angle.hpp>


acgm::Scene::Scene(std::shared_ptr<acgm::Camera> cam, 
    std::vector<std::shared_ptr<acgm::Model>> models, 
    std::shared_ptr<acgm::Light> light,
    const float bias, const float indexOfRefraction,
    const glm::vec3 enviroUp, const glm::vec3 enviroSeam,
    std::string imageFilePath)
    : camera_(cam), models_(models), light_(light), bias_(bias),
    indexOfRefraction_(indexOfRefraction), enviroUp_(enviroUp),
    enviroSeam_(enviroSeam)
{
    image_ = std::make_shared<acgm::Image>(imageFilePath);
}

void acgm::Scene::Raytrace(hiro::draw::PRasterRenderer &renderer) const
{
    glm::uint width = renderer->GetResolution().x;
    glm::uint height = renderer->GetResolution().y;
    float aspect = width / height;

    glm::vec3 v = camera_->UpDirection();
    glm::vec3 u = camera_->ForwardDirection();
    glm::vec3 w = glm::cross(u, v); 

    float fov = camera_->GetFieldOfView();
    float fovRad = glm::radians(fov);

    float y = tan(fovRad / 2.);
    float x = -aspect * y;

    float dy = 2.0f * tan(fovRad / 2.0f) / (float)height;
    float dx = 2.0f * aspect * tan(fovRad / 2.0f) / (float)width;

    float bias = 0.001f;

    for (int pixelY = height - 1; pixelY >= 0; pixelY--)    //rows
    {
        for (int pixelX = 0; pixelX < width; pixelX++)     //columns
        {
            glm::vec3 dir = glm::normalize(u + x * w + y * v);
            auto ray = std::make_shared<acgm::Ray>(camera_->GetPosition(), dir, bias);

            //initial values
            bool pixelSet = false;
            int minIndex = 0;
            std::optional<HitResult> hitResult;
            HitResult minHitResult;
            minHitResult.rayParam = INFINITY;
            
            //search for the closest model object
            for (int k = 0; k < models_.size(); k++)
            {
                std::shared_ptr<acgm::Model> model = models_.at(k);
                hitResult = model->ComputeIntersection(ray);

                if (hitResult == std::nullopt)
                {
                    continue;
                }

                float parameter = hitResult.value().rayParam;

                if (parameter >= 0 && parameter < minHitResult.rayParam)
                {
                    minIndex = k;
                    minHitResult = hitResult.value();
                    pixelSet = true;
                }
            }

            if (!pixelSet)  //if no object found, pixel is black
            {
                if (image_->Exists())
                {
                    auto normalizedView = glm::normalize(ray->GetDirection());
                    auto normalizedUp = glm::normalize(enviroUp_);
                    auto normalizedSeam = glm::normalize(enviroSeam_);
                    auto dotUpView = glm::dot(normalizedUp, normalizedView);
                    auto xVector = normalizedView - normalizedUp * dotUpView;

                    float latitude = std::acos(dotUpView);
                    float longitude = glm::orientedAngle(glm::normalize(xVector), normalizedSeam, normalizedUp);

                    float U = (longitude + PI) / (2 * PI);
                    float V = latitude / PI;
                    renderer->SetPixel(pixelX, pixelY, image_->GetColorAt(glm::vec2(U, V)));
                }
                else
                {
                    renderer->SetPixel(pixelX, pixelY, cogs::Color3f(0, 0, 0));
                }
            }
            else
            {
                //cast shadow ray to check if object is in shadow
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

                    //if something was hit and it is less than distance to light, pixel is in shadow
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

                renderer->SetPixel(pixelX, pixelY, models_.at(minIndex)->GetShader()->CalculateColor(shaderInput));
            }

            x += dx;
        }
        y -= dy;
        x = -tan(fovRad / 2.);
    }
}
