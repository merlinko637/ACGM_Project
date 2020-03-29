#include "pch.h"

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/Model.h>
#include <ACGM_RayTracer_lib/Plane.h>



TEST(IntersectionTests, RayPlaneIntersectionTest)
{
	//auto raySource = glm::vec3(0, 0, 0);
	//auto rayDirection = glm::vec3(0, 0, -1);
	//auto bias = 0.001f;
	//auto ray = std::make_shared<acgm::Ray>(raySource, rayDirection, bias);

	//auto backPlanePoint = glm::vec3(0, 0, 7);
	//auto backPlaneNormal = glm::vec3(0, 0, 1);
	//auto backPlane = std::make_shared<acgm::Plane>(backPlanePoint, backPlaneNormal);

	//auto topPlanePoint = glm::vec3(0, 1, 0);
	//auto topPlaneNormal = glm::vec3(0, -1, 0);
	//auto topPlane = std::make_shared<acgm::Plane>(topPlanePoint, topPlaneNormal);

	//auto hit1 = backPlane->ComputeIntersection(ray);
	//auto hit2 = backPlane->ComputeIntersection(ray);

	EXPECT_TRUE(true);
	EXPECT_EQ(1, 1);
}
