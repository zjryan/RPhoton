#include "./src/RPhotonEngine.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	// create console for debug
#if defined(DEBUG) || defined(_DEBUG)
	FILE *f(nullptr);
	if (AllocConsole())
	{
		freopen_s(&f, "CONOUT$", "w", stdout);
	}
#endif

	RPhotonEngine::initRPEngine(hInstance, L"RPhoton");
	RPhoton* RPEngine = RPhotonEngine::RPEngine();

	if (!RPEngine->Init())
	{
		return 1;
	}

	return RPEngine->Run();
}