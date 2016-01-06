#include "Material.h"
#include "Utilities.h"


Material::Material()
	:	color(Colors::Grey),
		texture(nullptr)
{
}

Material::Material(std::wstring texturepath)
	:	color(Colors::Grey),
		texture(nullptr)
{
	texture = new Texture(texturepath);
}

Material::~Material()
{
	Memory::SafeDelete(texture);
}

void Material::SetColor(const Color &c)
{
	color = c;
}

void Material::SetColor(float r, float g, float b)
{
	color = Color(r, g, b);
}

Color Material::SurfaceColor(const Vector2 &texCoord)
{
	Color retColor;
	if(texture != nullptr)
	{
		retColor = texture->Sample(texCoord);
	}
	else
	{
		retColor = color;
	}

	return retColor;
}

