#ifndef ZJR_RPHOTONENGINE_
#define ZJR_RPHOTONENGINE_

#include "RPhoton.h"

class RPhotonEngine
{
public:
	static void				initRPEngine(HINSTANCE hinstance, std::wstring title);
	static RPhoton*			RPEngine();

protected:
	RPhotonEngine() {}

private:
	static RPhoton*			g_RPhoton;
};

#endif
 