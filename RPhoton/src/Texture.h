#ifndef ZJR_TEXTURE_
#define ZJR_TEXTURE_

#include "../WinGDI/WinGDI.h"
#include "../GraphicLib/Vector2.h"

class Color;

class Texture
{
public:
	typedef Vector2 TextureCoord;
	enum FilterType
	{
		None,
		Linear,
		Cubic
	};

	Texture(std::wstring filename, FilterType filtertype = None);
	~Texture();

	Color				Sample(const TextureCoord &texcoord);

private:
	Color*				colors;
	int					texWidth;
	int					texHeight;
	FilterType			filterType;

	void				Load(std::wstring filename);
};

#endif
