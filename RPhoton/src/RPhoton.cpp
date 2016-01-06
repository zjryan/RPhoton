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
	Memory::SafeDelete(renderer);
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
	return InitViewer(windowName);
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
	environmentLight->SetIntensity(0.3f);
	environmentLight->SetColor(Colors::White);
	scene->environmentLight = environmentLight;

	// add scene objects & lights
	// objects

	Sphere* s1 = new Sphere();
	Material* m1 = new Material(L"Texture/Earth.bmp");
	s1->SetCenter(0.0f, 0.0f, 0.0f);
	s1->SetRadius(400.0f);
	s1->material = m1;
	scene->Add(s1);
	
	/*

	Sphere* s2 = new Sphere();
	s2->SetCenter(250.0f, 0.0f, -200.0f);
	s2->SetRadius(100.0f);
	s2->material->SetColor(Colors::Yellow);
	scene->Add(s2);

	Point a(-300.0f, 0.0f, 200.0f);
	Point b( 0.0f, 300.0f, 400.0f);
	Point c( 300.0f, 0.0f, 150.0f);
	Triangle* t1 = new Triangle(a, c, b);
	t1->material->SetColor(Colors::Green);
	scene->Add(t1);*/


/*
	Point p1(0.0f, 00.0f, 0.0f);
	Cube *c1 = new Cube(p1, 350.0f);
	c1->material->SetColor(Colors::Red);
	scene->Add(c1);*/


	// lights
	PointLight* l1 = new PointLight();
	l1->SetPosition(250.0f, -500.0f, 0.0f);
	l1->SetIntensity(0.4f);
	l1->SetColor(Colors::White);
	scene->Add(l1);

	// create renderer
	Renderer* rd = new Renderer(scene, camera, bufferWidth, bufferHeight);
	renderer = rd;
}

void RPhoton::RenderScene(Scene* scene)
{
	renderer->TraceRay(bufferWidth, bufferHeight, screenWidth, screenHeight);
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
