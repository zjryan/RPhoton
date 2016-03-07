#ifndef ZJR_SIMULATOR_
#define ZJR_SIMULATOR_

#include "WinViewer.h"

class Simulator
{
public:
	Simulator(HINSTANCE hinstance);
	virtual ~Simulator() = 0;

	WinViewer*				viewer() const;
	Timer&					timer() const;

	void					resetTimer();
	void					stopTimer();
	void					calculateRenderingTime();

protected:
	bool					viewerInitialized(std::wstring title);

	WinViewer*				winViewer;
	HINSTANCE				hInstance;
	int						screenWidth;
	int						screenHeight;

};

#endif
