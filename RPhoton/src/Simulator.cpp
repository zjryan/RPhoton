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

Timer& Simulator::timer() const
{
	return winViewer->timer();
}

void Simulator::resetTimer()
{
	Timer &t = timer();
	t.reset();
}

void Simulator::stopTimer()
{
	Timer &t = timer();
	t.stop();
}

void Simulator::calculateRenderingTime()
{
	winViewer->calculateRenderingTime();
}

bool Simulator::viewerInitialized(std::wstring title)
{
	winViewer = new WinViewer(hInstance, screenWidth, screenHeight, title);
	if (!winViewer->initialized())
	{
		return false;
	}

	return true;
}
