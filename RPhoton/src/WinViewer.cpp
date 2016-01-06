#include "WinViewer.h"
#include <sstream>
#include <fstream>

WinViewer::WinViewer(HINSTANCE hinstance, std::wstring title)
	:	hInstance(hinstance),
		hWnd(nullptr),
		title(title),
		width(800),
		height(600)
{
}

WinViewer::WinViewer(HINSTANCE hinstance, int width, int height, std::wstring title)
	:	hInstance(hinstance),
		hWnd(nullptr),
		title(title),
		width(width),
		height(height)
{
}

WinViewer::~WinViewer()
{
}

bool WinViewer::Init()
{
	if (!InitWindow())
	{
		return false;
	}

	return true;
}

int WinViewer::Run()
{
	MSG msg = { 0 };

	//timer.Reset();
	//UpdateWindow(hWnd);


	//timer.Stop();
	//CalculateRenderingTime();

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

bool WinViewer::InitWindow()
{
	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MsgProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.lpszClassName = title.c_str();
	wc.lpszMenuName = nullptr;

	if (!RegisterClass(&wc))
	{
		MessageBox(nullptr, L"Register Window Class Failed", L"Error", MB_OK);
		return false;
	}

	UINT posX, posY;

	posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

	hWnd = CreateWindow(title.c_str(), title.c_str(),
		WS_OVERLAPPEDWINDOW,
		posX, posY,
		width, height,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);
	
	return true;

}

void WinViewer::CalculateRenderingTime()
{
	float elapsedTime = timer.TotalTime();

	std::wostringstream text;
	text.precision(5);
	text << L"            Elapsed Time: "
		<< elapsedTime
		<< L" s";

	std::wstring newtitle = title + text.str();
	SetWindowText(hWnd, newtitle.c_str());
}

LRESULT WinViewer::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
