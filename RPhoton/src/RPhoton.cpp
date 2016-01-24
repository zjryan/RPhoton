#include "RPhoton.h"
#include "Camera.h"
#include "Scene.h"
#include "Renderer.h"
#include "PointLight.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Cube.h"
#include "Utilities.h"
#include <iostream>

RPhoton::RPhoton(HINSTANCE hinstance, std::wstring title)
	:	Simulator(hinstance),
		renderer(nullptr),
		parser(nullptr),
		appTitle(title)
{
}

RPhoton::~RPhoton()
{
	Memory::safeDelete(renderer);
}

bool RPhoton::Init()
{
	// 1. import config file
	if (!ImportSysConfig(L""))
	{
		MessageBox(NULL, L"Read Configuration File Failed", L"Error", MB_OK);
		return false;
	}

	// 2. create window
	if (!CreateMainWindow(appTitle))
	{
		MessageBox(NULL, L"Cannot Create Window", L"Error", MB_OK);
		return false;
	}

	// 3. build image buffer
	BuildImageBuffer();

	// 4. build render scene
	BuildScene();

	return true;
}

int RPhoton::Run()
{
	// 1. render
	RenderScene(nullptr);

	// 2. present
	PresentImage();

	// 3. message loop
	return winViewer->Run();
}

bool RPhoton::ImportSysConfig(std::wstring)
{
	screenWidth = 800;
	screenHeight = 600;
	bufferWidth = 800;
	bufferHeight = 600;
	return true;
}

bool RPhoton::CreateMainWindow(std::wstring windowName)
{
	return viewerInitialized(windowName);
}

void RPhoton::BuildImageBuffer()
{
	imageBuffer = new COLORREF[bufferWidth * bufferHeight];
}

void RPhoton::BuildScene()
{
	// create camera
	Camera* camera = new Camera();

	// create scene
	Scene* scene = new Scene();

	// create environment light
	Light* environmentLight = new Light();
	environmentLight->setIntensity(0.3f);
	environmentLight->setColor(Colors::White);
	scene->environmentLight = environmentLight;

	// add scene objects & lights
	// objects
	Sphere* s1 = new Sphere();
	Material* m1 = new Material(L"Texture/Earth.bmp");
	s1->setCenter(0.0f, 0.0f, 0.0f);
	s1->setRadius(270.0f);
	s1->material = m1;
	scene->add(s1);
	
	Sphere* s2 = new Sphere();
	s2->setCenter(550.0f, 300.0f, -200.0f);
	s2->setRadius(150.0f);
	s2->material->SetColor(Colors::Red);
	scene->add(s2);

	Point p1(-550.0f, 300.0f, -200.0f);
	Cube *c1 = new Cube(p1, 250.0f);
	c1->material->SetColor(Colors::Green);
	scene->add(c1);

	// lights
	PointLight* l1 = new PointLight();
	l1->setPosition(250.0f, -500.0f, 0.0f);
	l1->setIntensity(0.4f);
	l1->setColor(Colors::White);
	scene->add(l1);

	// create renderer
	Renderer* rd = new Renderer(scene, camera, bufferWidth, bufferHeight);
	renderer = rd;
}

void RPhoton::RenderScene(Scene* scene)
{
	renderer->traceRay(bufferWidth, bufferHeight, screenWidth, screenHeight);
}

void RPhoton::PresentImage()
{
	auto renderColors = renderer->colors;

	for (int y = 0; y < bufferHeight; y++)
	{
		for (int x = 0; x < bufferWidth; x++)
		{
			auto index = x + y * bufferWidth;
			Color::_RGB_ curColor = renderColors[index].Standlize();
			imageBuffer[index] = RGB(curColor.R, curColor.G, curColor.B);
		}
	}

	auto hwnd = winViewer->GetWindowHandle();
	UpdateWindow(hwnd);
}

LRESULT RPhoton::DrawProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC				hdc;
	PAINTSTRUCT		ps;
	
	hdc = BeginPaint(hwnd, &ps);

	for (int y = 0; y < bufferHeight; y++)
	{
		for (int x = 0; x < bufferWidth; x++)
		{
			auto index = x + y * bufferWidth;
			SetPixel(hdc, x, y, imageBuffer[index]);
		}
	}

	EndPaint(hwnd, &ps);
	return 0;
}
