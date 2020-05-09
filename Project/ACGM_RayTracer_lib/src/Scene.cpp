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
    refractiveIndex_(indexOfRefraction), enviroUp_(enviroUp),
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

    for (int pixelY = height - 1; pixelY >= 0; pixelY--)    //rows
    {
        for (int pixelX = 0; pixelX < width; pixelX++)     //columns
        {
            glm::vec3 dir = glm::normalize(u + x * w + y * v);
            auto ray = std::make_shared<acgm::Ray>(camera_->GetPosition(), dir, bias_);

            auto pixelColor = CalculatePixelColor(ray, 10, 10 );
            renderer->SetPixel(pixelX, pixelY, pixelColor);

            x += dx;
        }
        y -= dy;
        x = -tan(fovRad / 2.);
    }
}

cogs::Color3f acgm::Scene::CalculatePixelColor(std::shared_ptr<acgm::Ray> ray, int maxReflectionDepth, int maxTransparencyDepth) const
{
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

        if (parameter > 0.01f && parameter < minHitResult.rayParam)
        {
            minIndex = k;
            minHitResult = hitResult.value();
            pixelSet = true;
        }
    }

    if (!pixelSet)  //if no object found, pixel is black
    {
        return NoObjectHit(ray->GetDirection());
    }

    //cast shadow ray to check if object is in shadow
    HitResult minShadowHitResult;
    minShadowHitResult.rayParam = INFINITY;

    auto point = minHitResult.point;
    bool isInShadow = false;
    auto directionToLight = glm::normalize(light_->GetDirectionToLight(point));
    auto shadowRay = std::make_shared<acgm::Ray>(point + minHitResult.normal * bias_, directionToLight, bias_);
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
        if (shadowHit.value().rayParam > bias_ && shadowHit.value().rayParam < distanceToLight)
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

    ShaderOutput output = models_.at(minIndex)->GetShader()->CalculateColor(shaderInput);
    auto transparencyColor = cogs::Color3f(0, 0, 0);

    if (output.transparency > 0.0f && maxTransparencyDepth > 0)
    {
        auto direction = ray->GetRefractionDirection(refractiveIndex_, output.refractiveIndex, shaderInput.normal);
        if (!direction.has_value())
        {
            direction = ray->GetReflectionDirection(shaderInput.normal);
        }

        auto transparentRay = std::make_shared<acgm::Ray>(shaderInput.point, direction.value(), bias_);
        transparencyColor = output.transparency * CalculatePixelColor(transparentRay, maxReflectionDepth, --maxTransparencyDepth);
    }

    if ((glm::epsilonEqual<float>(output.glossiness, 0.0f, glm::epsilon<float>())) || maxReflectionDepth == 0)
    {
        return output.color * (1 - output.transparency) + transparencyColor;
    }

    auto reflectedDirection = ray->GetReflectionDirection(shaderInput.normal);
    auto reflectionRay = std::make_shared<acgm::Ray>(shaderInput.point, reflectedDirection, bias_);

    return output.color * (1 - output.glossiness - output.transparency) + output.glossiness * CalculatePixelColor(reflectionRay, --maxReflectionDepth, maxTransparencyDepth);
}

cogs::Color3f acgm::Scene::NoObjectHit(glm::vec3 direction) const 
{
    if (!image_->Exists())
    {
        return cogs::Color3f(0, 0, 0);
    }

    auto normalizedView = glm::normalize(direction);
    auto normalizedUp = glm::normalize(enviroUp_);
    auto normalizedSeam = glm::normalize(enviroSeam_);
    auto dotUpView = glm::dot(normalizedUp, normalizedView);
    auto xVector = normalizedView - normalizedUp * dotUpView;

    float latitude = std::acos(dotUpView);
    float longitude = glm::orientedAngle(glm::normalize(xVector), normalizedSeam, normalizedUp);

    float U = (longitude + PI) / (2 * PI);
    float V = latitude / PI;
    return image_->GetColorAt(glm::vec2(U, V));
}