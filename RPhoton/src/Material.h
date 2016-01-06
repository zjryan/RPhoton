#ifndef ZJR_MATERIAL_
#define ZJR_MATERIAL_

#include "../GraphicLib/Color.h"
#include "../src/Texture.h"

class Material
{
public:
	Material();
	~Material();

	void				SetColor(const Color &c);
	void				SetColor(float r, float g, float b);
	Color				GetColor();

	Color				color;
	Texture*			texture;
};

#endif
