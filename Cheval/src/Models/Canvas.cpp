
#include "../Headers/Models/Canvas.h"
#include "../Headers/Helpers/Utils.h"

#include <cstdlib>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_WINDOWS_UTF8 

#include "../../3rdParty/stb_image_write.h"


Canvas::Canvas(int height, int width)
	: height_( height),
	  width_ (width),
	  screen_ (nullptr)
{
	auto const size = width_ * height_ ;
	screen_ = static_cast<Colour*>(calloc(size, sizeof(Colour)));
}

Canvas::~Canvas()
{
	if (screen_ != nullptr)
	{
		free(screen_);
		screen_ = nullptr;
	}
}

int Canvas::write_file(char const* filename) const
{
	auto const size = width_ * height_ * 3;
	auto *Data = new uint8_t[size];

	auto index = 0;
	for (auto i = 0; i < height_ * width_; ++i)
	{
		auto c = screen_[i];

		const auto ir = static_cast<uint8_t>(Clamp(static_cast<int>(std::round(c.R() * 255.999f)), 0, 255));
		const auto ig = static_cast<uint8_t>(Clamp(static_cast<int>(std::round(c.G() * 255.999f)), 0, 255));
		const auto ib = static_cast<uint8_t>(Clamp(static_cast<int>(std::round(c.B() * 255.999f)), 0, 255));

			Data[index++] = ir;
			Data[index++] = ig;
			Data[index++] = ib;			
	}
	
	const auto success = stbi_write_jpg(filename, width_, height_, 3, Data, 100);

	delete[] Data;
	return success;
}

void Canvas::write_pixel(int x, int y, Colour const& colour) const
{
	if (x >= width_ || y >= height_) return; 

	screen_[x + (width_ * y)] = colour;
}

Colour Canvas::pixel_at(int x, int y) const
{
	return screen_[x + width_ * y];
}


