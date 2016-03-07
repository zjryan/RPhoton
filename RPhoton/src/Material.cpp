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
	Memory::safeDelete(texture);
}

void Material::setColor(const Color &c)
{
	color = c;
}

void Material::setColor(float r, float g, float b)
{
	color = Color(r, g, b);
}

Color Material::surfaceColor(const Vector2 &texCoord)
{
	Color retColor;
	if(texture != nullptr)
	{
		retColor = texture->sample(texCoord);
	}
	else
	{
		retColor = color;
	}

	return retColor;
}

