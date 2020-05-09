#include <ACGM_RayTracer_lib/Mesh.h>
#include <COGS/Transform.h>

acgm::Mesh::Mesh(std::string path, const glm::mat4 transform)
{
	bool result = mesh_.Import(path);
	mesh_.points->Transform(transform);
}

std::optional<acgm::HitResult> acgm::Mesh::ComputeIntersection(std::shared_ptr<acgm::Ray> ray)
{
    auto faces = mesh_.faces->GetFaces();
    auto pointsPositions = mesh_.points->GetPositions();
    
    HitResult minHit;
    minHit.rayParam = INFINITY;

    int faceCount = mesh_.faces->GetFaceCount();

    for (int j = 0; j < faceCount; j++)
    {
        auto faceX = faces[j].x;
        auto faceY = faces[j].y;
        auto faceZ = faces[j].z;

        auto hitResult = ComputeTriangleIntersection(
            pointsPositions[faceX], pointsPositions[faceY], pointsPositions[faceZ], ray);

        if (hitResult == std::nullopt)
        {
            continue;
        }

        float parameter = hitResult.value().rayParam;

        if (parameter > ray->GetBias() && parameter < minHit.rayParam)
        {
            minHit = hitResult.value();
        }
    }

    return minHit;
}

std::optional<acgm::HitResult> acgm::Mesh::ComputeTriangleIntersection(
    glm::vec3 &x, glm::vec3 &y, glm::vec3 &z, std::shared_ptr<acgm::Ray> ray)
{
    glm::vec3 e1 = y - x;
    glm::vec3 e2 = z - x;

    glm::vec3 P = glm::cross(ray->GetDirection(), e2);
    float determinant = glm::dot(e1, P);

    if (glm::epsilonEqual<float>(determinant, 0.0f, glm::epsilon<float>()))
    {
        return std::nullopt;    
    }

    float inverseDet = 1.0 / determinant;
    glm::vec3 distance = ray->GetOrigin() - x;
    float u = inverseDet * glm::dot(distance, P);

    if (u <= 0.0 || u > 1.0)
    {
        return std::nullopt;    
    }

    glm::vec3 Q = glm::cross(distance, e1);
    float v = inverseDet * glm::dot(ray->GetDirection(), Q);

    if (v <= 0.0 || u + v > 1.0)
    {
        return std::nullopt;    
    }

    float t = inverseDet * glm::dot(e2, Q);

    HitResult hit;
    hit.rayParam = t;
    hit.normal = glm::cross(y - x, z - x);
    hit.point = ray->GetPoint(t) + hit.normal * ray->GetBias();

    return hit;
}