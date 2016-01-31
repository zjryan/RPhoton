#ifndef ZJR_RPHOTON_
#define ZJR_RPHOTON_

#include "Simulator.h"

class Renderer;
class Parser;
class Scene;

class RPhoton : public Simulator
{
public:
	RPhoton(HINSTANCE hinstance, std::wstring title);
	~RPhoton();

	bool				initialized();
	int					run();
	LRESULT				drawProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool				systemConfigInitialized(std::wstring configPath);
	bool				mainWindowCreated(std::wstring windowName);
	void				buildImageBuffer();
	void				buildScene();
	void				renderScene(Scene* scene);
	void				presentImage();

private:
	Renderer*			renderer;
	Parser*				parser;

	//image buffer
	int					bufferWidth;
	int					bufferHeight;
	COLORREF*			imageBuffer;

	//app name
	std::wstring		appTitle;
};

#endif
