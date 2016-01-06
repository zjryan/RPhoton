#ifndef ZJR_TEXTURE_
#define ZJR_TEXTURE_

#include "../WinGDI/WinGDI.h"
class Color;

struct Vector2
{
	float x;
	float y;

	Vector2() {}
	Vector2(float x_, float y_) : x(x_), y(y_) {}
	Vector2& operator=(const Vector2 &rhs);
};

inline Vector2& Vector2::operator=(const Vector2 &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}
	
	x = rhs.x;
	y = rhs.y;
	return *this;
}

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

	Texture(std::wstring filename, FilterType filtertype);
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
