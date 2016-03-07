#include "WinViewer.h"
#include "RPhotonEngine.h"

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	auto RPEgine = RPhotonEngine::RPEngine();
	auto winViewer = RPEgine->viewer();

	if (RPEgine != nullptr && msg == WM_PAINT)
	{
		return RPEgine->drawProc(hwnd, msg, wParam, lParam);
	}

	if (winViewer != nullptr)
	{
		return winViewer->wndProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
