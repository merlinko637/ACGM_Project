#pragma once

#include <ACGM_RayTracer_lib/Model.h>
#include <COGS/Mesh.h>



namespace acgm
{
	class Mesh : public Model
	{
	public:
		explicit Mesh(std::string path, const glm::mat4 transform);
		virtual ~Mesh() = default;

		//computes intersection between given ray and mesh
		std::optional<acgm::HitResult> ComputeIntersection(std::shared_ptr<acgm::Ray> ray) override;

	private:
		//computes intersection between given ray and triangle coordinates
		std::optional<acgm::HitResult> ComputeTriangleIntersection(
			glm::vec3 &x, glm::vec3 &y, glm::vec3 &z, std::shared_ptr<acgm::Ray> ray);

		cogs::Mesh mesh_;
	};


}

