#include "WinViewer.h"
#include <sstream>
#include <fstream>

WinViewer::WinViewer(HINSTANCE hinstance, std::wstring title)
	:	_hInstance(hinstance),
		_hWnd(nullptr),
		_title(title),
		_width(800),
		_height(600)
{
}

WinViewer::WinViewer(HINSTANCE hinstance, int width, int height, std::wstring title)
	:	_hInstance(hinstance),
		_hWnd(nullptr),
		_title(title),
		_width(width),
		_height(height)
{
}

WinViewer::~WinViewer()
{
}

bool WinViewer::initialized()
{
	if (!windowInitialized())
	{
		return false;
	}

	return true;
}

int WinViewer::run()
{
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

bool WinViewer::windowInitialized()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = _hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszClassName = _title.c_str();
	wc.lpszMenuName = nullptr;

	if (!RegisterClass(&wc))
	{
		MessageBox(nullptr, L"Register Window Class Failed", L"Error", MB_OK);
		return false;
	}

	UINT posX, posY;

	posX = (GetSystemMetrics(SM_CXSCREEN) - _width) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - _height) / 2;

	_hWnd = CreateWindow(_title.c_str(), _title.c_str(),
		WS_OVERLAPPEDWINDOW,
		posX, posY,
		_width, _height,
		NULL, NULL, _hInstance, NULL);

	ShowWindow(_hWnd, SW_SHOW);
	
	return true;

}

void WinViewer::calculateRenderingTime()
{
	float elapsedTime = _timer.totalTime();

	std::wostringstream text;
	text.precision(5);
	text << L"            Elapsed Time: "
		<< elapsedTime
		<< L" s";

	std::wstring newtitle = _title + text.str();
	SetWindowText(_hWnd, newtitle.c_str());
}

LRESULT WinViewer::wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
}
