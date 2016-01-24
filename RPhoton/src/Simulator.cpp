#include "Simulator.h"
#include "Utilities.h"

Simulator::Simulator(HINSTANCE hinstance)
	:	hInstance(hinstance)
{
}

Simulator::~Simulator()
{
	Memory::safeDelete(winViewer);
}

WinViewer* Simulator::viewer() const
{
	return winViewer;
}

bool Simulator::viewerInitialized(std::wstring title)
{
	winViewer = new WinViewer(hInstance, screenWidth, screenHeight, title);
	if (!winViewer->Init())
	{
		return false;
	}

	return true;
}
