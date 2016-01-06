#ifndef ZJR_CAMERA_
#define ZJR_CAMERA_

#include "../GraphicLib/Ray.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void							Update();
	void							Update(const Point &eye, const Point &lookAt);
	Ray								GenerateRay(int x, int y, int bufferWidth, int bufferheight, int screenWidth, int screenHeight);

private:
	Point							eyePosition;
	Point							lookAtPosition;
	Vector							up;
	Vector							u, v, w;
	float							eyeDistance;
};

#endif
