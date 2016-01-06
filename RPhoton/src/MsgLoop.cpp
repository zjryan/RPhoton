#include "WinViewer.h"
#include "RPhotonEngine.h"

LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	auto RPEgine = RPhotonEngine::RPEngine();
	auto winViewer = RPEgine->GetViewer();

	if (RPEgine != nullptr && msg == WM_PAINT)
	{
		return RPEgine->DrawProc(hwnd, msg, wParam, lParam);
	}

	if (winViewer != nullptr)
	{
		return winViewer->WndProc(hwnd, msg, wParam, lParam);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
