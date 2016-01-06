#ifndef ZJR_RPHOTONENGINE_
#define ZJR_RPHOTONENGINE_

#include "RPhoton.h"

class RPhotonEngine
{
public:
	static void				InitRPEngine(HINSTANCE hinstance, std::wstring title);
	static RPhoton*			RPEngine();

protected:
	RPhotonEngine() {}

private:
	static RPhoton*			g_RPhoton;
};

#endif
