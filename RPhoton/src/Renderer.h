#ifndef ZJR_RENDERER_
#define ZJR_RENDERER_

class Scene;
class Color;
class Camera;

class Renderer
{
public:
	Scene*							scene;
	Camera*							camera;
	Color*							colors;

	Renderer(Scene *scene, Camera *camera,int bufferWidth, int bufferHeight);
	~Renderer();

	void TraceRay(int bufferWidth, int bufferHeight, int screenWidth, int screenHeight);
};

#endif
