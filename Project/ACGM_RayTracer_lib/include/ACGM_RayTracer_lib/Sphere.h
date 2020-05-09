#pragma once
#include <ACGM_RayTracer_lib/Model.h>



namespace acgm
{
	class Sphere : public Model
	{
	public:
		Sphere(const glm::vec3 &position, float radius);
		virtual ~Sphere() = default;
		
		//computes intersection between ray and sphere
		std::optional<acgm::HitResult> ComputeIntersection(std::shared_ptr<acgm::Ray> ray) override;

		//returns sphere position
		const glm::vec3 &GetPosition() const;

		//returns sphere radius
		float GetRadius() const;
	
	private:
		glm::vec3 position_;
		const float radius_;
	};
}
