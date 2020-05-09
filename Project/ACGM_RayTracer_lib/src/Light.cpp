#include <ACGM_RayTracer_lib/Light.h>


acgm::Light::Light(float intensity) : intensity_(intensity)
{

}

const float acgm::Light::GetIntensity()
{
	return intensity_;
}