#include "Texture.h"
#include "Utilities.h"
#include "../GraphicLib/Color.h"
#include <iostream>


using namespace WinGDI;

Texture::Texture(std::wstring filename, FilterType filtertype)
	:	filterType(filtertype)
{
	Load(filename);
}

Texture::~Texture()
{
	Memory::safeDeleteArray(colors);
}


Color Texture::sample(const TextureCoord &texcoord)
{
	float x = texcoord.x * texWidth;
	float y = texcoord.y * texHeight;
	int ix = (static_cast<int>(x) % texWidth + texWidth) % texWidth;
	int iy = (static_cast<int>(y) % texHeight + texHeight) % texHeight;

	Color retColor(color(ix, iy));

	switch(filterType)
	{
	case Linear:
		//..
		break;
	case Cubic:
		//..
		break;
	default:
		break;
	}
	return retColor;
}

Color Texture::color(int x, int y)
{
	return colors[x + y * texWidth];
}

void Texture::Load(std::wstring filename)
{
	Memory::safeDeleteArray(colors);
	WinBitmap texture(filename);
	texWidth = texture.GetWidth();
	texHeight = texture.GetHeight();
	colors = new Color[texWidth * texHeight];

	auto pixels = texture.GetPixelBits();
	for (auto y = 0; y < texHeight; y++)
	{
		for (auto x = 0; x < texWidth; x++)
		{
			auto index = x + y * texWidth;
			colors[index].r = static_cast<float>(pixels[index * 3 + 2]) / 255.0f;
			colors[index].g = static_cast<float>(pixels[index * 3 + 1]) / 255.0f;
			colors[index].b = static_cast<float>(pixels[index * 3 + 0]) / 255.0f;
		}
	}
}
