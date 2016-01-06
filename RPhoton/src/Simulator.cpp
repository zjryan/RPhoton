#include "Simulator.h"
#include "Utilities.h"

Simulator::Simulator(HINSTANCE hinstance)
	:	hInstance(hinstance)
{
}

Simulator::~Simulator()
{
	Memory::SafeDelete(winViewer);
}

WinViewer* Simulator::GetViewer() const
{
	return winViewer;
}

bool Simulator::InitViewer(std::wstring title)
{
	winViewer = new WinViewer(hInstance, screenWidth, screenHeight, title);
	if (!winViewer->Init())
	{
		return false;
	}

	return true;
}
