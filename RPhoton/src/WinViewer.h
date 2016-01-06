#ifndef ZJR_WINVIEWER_
#define ZJR_WINVIEWER_

#include <windows.h>
#include <string>
#include "Timer.h"

class WinViewer
{
public:
	WinViewer(HINSTANCE hinstance, std::wstring title = L"Ray Tracer");
	WinViewer(HINSTANCE hinstance, int width, int height, std::wstring title = L"Ray Tracer");
	WinViewer(const WinViewer &wv) = delete;
	~WinViewer();

	HINSTANCE				getInstance() const;
	HWND					GetWindowHandle() const;
	bool					Init();
	int						Run();
	LRESULT					WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool					InitWindow();
	void					CalculateRenderingTime();

private:

	HINSTANCE				hInstance;
	HWND					hWnd;
	std::wstring			title;
	UINT					width;
	UINT					height;
	Timer					timer;
};

inline HINSTANCE WinViewer::getInstance() const
{
	return hInstance;
}

inline HWND WinViewer::GetWindowHandle() const
{
	return hWnd;
}

extern LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
