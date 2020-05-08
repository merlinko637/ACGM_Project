#pragma once
#include <glm\detail\type_vec.hpp>
#include <string>
#include <COGS\Color.h>


namespace acgm
{
	class Image
	{
	public:
		Image(std::string imageFilePath);
		~Image();

		cogs::Color3f GetColorAt(const glm::vec2 &uvs) const;
		bool Exists();

	private:
		bool exists_ = false;
		uint8_t* imageData_;
		int width_;
		int height_;
	};
}


