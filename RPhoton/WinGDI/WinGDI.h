#ifndef ZJR_WINGDI_
#define ZJR_WINGDI_

#include <Windows.h>
#include <string>

namespace WinGDI
{
	class WinBitmap
	{
	public:
		WinBitmap(std::wstring filename);
		~WinBitmap();

		UINT					GetWidth() const;
		UINT					GetHeight() const;
		HBITMAP					GetBitmap() const;
		BYTE*					GetPixelBits() const;

	protected:
		UINT					Bmbits;
		UINT					Bmwidth;
		UINT					Bmheight;
		HBITMAP					BmHandle;
		BYTE*					BmPixelBits;

		void					Init(std::wstring filename);
		void					Load(std::wstring filename);
	};
}

#endif
