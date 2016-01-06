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

	bool				Init();
	int					Run();
	LRESULT				DrawProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	bool				ImportSysConfig(std::wstring configPath);
	bool				CreateMainWindow(std::wstring windowName);
	void				BuildImageBuffer();
	void				BuildScene();
	void				RenderScene(Scene* scene);
	void				PresentImage();

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
