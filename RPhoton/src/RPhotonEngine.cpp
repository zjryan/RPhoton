#include "RPhotonEngine.h"

RPhoton* RPhotonEngine::g_RPhoton = nullptr;

void RPhotonEngine::initRPEngine(HINSTANCE hinstance, std::wstring title)
{
	if (g_RPhoton == nullptr)
	{
		g_RPhoton = new RPhoton(hinstance, title);
	}
}

RPhoton* RPhotonEngine::RPEngine()
{
	return g_RPhoton;
}
