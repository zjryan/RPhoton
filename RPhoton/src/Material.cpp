#include "Material.h"
#include "Utilities.h"


Material::Material()
	:	color(Colors::Grey),
		texture(nullptr)
{
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

