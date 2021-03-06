#include "raytracer.cpp"
#include "color.h"
#include "../lib/gentle_giant.hpp"

const int samples_per_pixel = 10;
const int max_color = 255;

const RenderBuffer* renderBufferPointer;;

void DrawPixel(int x, int y, vec3 pixel_data)
{
	float r = pixel_data.x();
	float g = pixel_data.y();
	float b = pixel_data.z();

	// Divide the color by the number of samples and gamma-correct got gamma=2.0
	float scale = 1.0f / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	const float char_conversion = 256.0f;
	const float min_color = 0.0f;
	const float max_color = 0.999f;
	int ir = static_cast<int>(char_conversion * clamp(r, min_color, max_color));
	int ig = static_cast<int>(char_conversion * clamp(g, min_color, max_color));
	int ib = static_cast<int>(char_conversion * clamp(b, min_color, max_color));

	uint32_t color = gentle::GetColorFromRGB(ir, ig, ib);
	gentle::PlotPixel(*renderBufferPointer, color, x, y);
}

void gentle::Initialize(const GameMemory &gameMemory, const RenderBuffer &renderBuffer)
{
	const int image_width = renderBuffer.width;
	const int image_height = renderBuffer.height;

	renderBufferPointer = &renderBuffer;

	ray_trace(image_width, image_height, max_color, samples_per_pixel, &DrawPixel);
}


void gentle::UpdateAndRender(const GameMemory &gameMemory, const Input &input, const RenderBuffer &renderBuffer, float dt)
{

}
