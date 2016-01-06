#include "WinGDI.h"

namespace WinGDI
{
	WinBitmap::WinBitmap(std::wstring filename)
	{
		Load(filename);
	}

	WinBitmap::~WinBitmap()
	{
		if (BmPixelBits)
		{
			delete[] BmPixelBits;
		}

		if (BmHandle)
		{
			DeleteObject(BmHandle);
		}
	}

	void WinBitmap::Init(std::wstring filename)
	{
		BITMAPFILEHEADER	bmHeader;
		BITMAPINFO*			bmInfo;
		HANDLE				filehandle;

		filehandle = CreateFile(filename.c_str(), GENERIC_READ, FILE_SHARE_READ,
			NULL, OPEN_EXISTING, 0, NULL);
		//读文件失败，BmHandle设置为NULL
		if (filehandle == INVALID_HANDLE_VALUE)
		{
			BmHandle = NULL;
			return;
		}

		//读文件头
		DWORD bytesRead;
		bool succeed = ReadFile(filehandle, &bmHeader, sizeof(BITMAPFILEHEADER),
			&bytesRead, NULL);

		if (!succeed || bytesRead != sizeof(BITMAPFILEHEADER)
			|| bmHeader.bfType != 0x4d42)
		{
			CloseHandle(filehandle);
			BmHandle = NULL;
			return;
		}

		//读信息头
		DWORD bmInfoSize = bmHeader.bfOffBits - sizeof(BITMAPFILEHEADER);
		bmInfo = new BITMAPINFO[bmInfoSize];

		succeed = ReadFile(filehandle, bmInfo, bmInfoSize, &bytesRead, NULL);
		if (!succeed || bytesRead != bmInfoSize)
		{
			delete[] bmInfo;
			CloseHandle(filehandle);
			BmHandle = NULL;
			return;
		}

		BmHandle = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (void**)&BmPixelBits, NULL, 0);
		if (BmHandle == NULL)
		{
			delete[] bmInfo;
			CloseHandle(filehandle);
			return;
		}

		BITMAP tempBitmap;
		GetObject(BmHandle, sizeof(BITMAP), &tempBitmap);
		Bmwidth = tempBitmap.bmWidth;
		Bmheight = tempBitmap.bmHeight;
		Bmbits = tempBitmap.bmBitsPixel;
		ReadFile(filehandle, BmPixelBits, bmHeader.bfSize - bmHeader.bfOffBits,
			&bytesRead, NULL);

		delete[] bmInfo;
		CloseHandle(filehandle);
	}

	void WinBitmap::Load(std::wstring filename)
	{
		HBITMAP tempHbitmap = (HBITMAP)LoadImage(NULL, filename.c_str(),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		BITMAP tempRec;
		GetObject(tempHbitmap, sizeof(BITMAP), &tempRec);
		Bmwidth = tempRec.bmWidth;
		Bmheight = tempRec.bmHeight;
		Bmbits = tempRec.bmBitsPixel;
		auto memsize = Bmwidth * Bmheight * Bmbits / 8;
		BmPixelBits = new BYTE[memsize];
		memcpy((void*)BmPixelBits, (void*)tempRec.bmBits, memsize);
		DeleteObject(tempHbitmap);
	}

	UINT WinBitmap::GetWidth() const
	{
		return Bmwidth;
	}

	UINT WinBitmap::GetHeight() const
	{
		return Bmheight;
	}

	HBITMAP WinBitmap::GetBitmap() const
	{
		return BmHandle;
	}

	BYTE* WinBitmap::GetPixelBits() const
	{
		return BmPixelBits;
	}
}
