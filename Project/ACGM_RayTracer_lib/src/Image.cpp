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

cogs::Color3b acgm::Image::GetColorAt(const glm::vec2& uvs) const
{
	uint32_t x = uint32_t(uvs.x * width_);
	uint32_t y = uint32_t(uvs.y * height_);
	uint32_t offset = ((y - 1) * width_ + x) * 3;

	return cogs::Color3b(imageData_[offset], imageData_[offset + 1], imageData_[offset + 2]);
}

bool acgm::Image::Exists()
{
	return exists_;
}