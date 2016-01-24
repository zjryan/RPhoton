#include "Renderer.h"
#include "Scene.h"
#include "Camera.h"
#include "Utilities.h"
#include "../GraphicLib/Color.h"
#include "../GraphicLib/Ray.h"

Renderer::Renderer(Scene *scene_, Camera *camera_, int bufferWidth, int bufferHeight)
{
	scene = scene_;
	camera = camera_;
	colors = new Color[bufferWidth * bufferHeight];
}

Renderer::~Renderer()
{
	Memory::safeDelete(scene);
	Memory::safeDeleteArray(colors);
}

void Renderer::traceRay(int bufferWidth, int bufferHeight, int screenWidth, int screenHeight)
{
	for (int y = 0; y < bufferHeight; y++)
	{
		for (int x = 0; x < bufferWidth; x++)
		{
			auto index = x + y * bufferWidth;
			Ray mainRay = camera->GeneratedRay(x, y, bufferWidth, bufferHeight, screenWidth, screenHeight);
			colors[index] = scene->Shaded(mainRay);
		}
	}
}
