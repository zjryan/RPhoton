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

	bool					initialized();
	int						run();
	LRESULT					wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	HINSTANCE				instance() const;
	HWND					windowHandle() const;
	Timer&					timer();
	void					calculateRenderingTime();

private:
	bool					windowInitialized();

private:

	HINSTANCE				_hInstance;
	HWND					_hWnd;
	std::wstring			_title;
	UINT					_width;
	UINT					_height;
	Timer					_timer;
};

inline HINSTANCE WinViewer::instance() const
{
	return _hInstance;
}

inline HWND WinViewer::windowHandle() const
{
	return _hWnd;
}

inline Timer& WinViewer::timer()
{
	return _timer;
}

extern LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif
