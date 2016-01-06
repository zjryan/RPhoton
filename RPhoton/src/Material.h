#ifndef ZJR_MATERIAL_
#define ZJR_MATERIAL_

#include "../GraphicLib/Color.h"
#include "../src/Texture.h"

class Material
{
public:
	Material();
	Material(std::wstring texturepath);
	~Material();

	void				SetColor(const Color &c);
	void				SetColor(float r, float g, float b);
	Color				SurfaceColor(const Vector2 &texCoord);

	Color				color;
	Texture*			texture;
};

#endif
