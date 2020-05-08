#include <ACGM_RayTracer_lib/Image.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


acgm::Image::Image(std::string imageFilePath)
{
	if (!imageFilePath.empty())
	{
		exists_ = true;
		imageData_ = stbi_load(imageFilePath.c_str(), &width_, &height_, NULL, 3);
	}
}

acgm::Image::~Image()
{
	stbi_image_free(imageData_);
}

cogs::Color3f acgm::Image::GetColorAt(const glm::vec2& uvs) const
{
	uint32_t x = uint32_t(uvs.x * width_);
	uint32_t y = uint32_t(uvs.y * height_);
	uint32_t offset = ((y - 1) * width_ + x) * 3;
	
	float r = imageData_[offset++] / 255.0f;
	float g = imageData_[offset++] / 255.0f;
	float b = imageData_[offset] / 255.0f;

	return cogs::Color3f(r, g, b);
}

bool acgm::Image::Exists()
{
	return exists_;
}