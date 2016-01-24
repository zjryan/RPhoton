#ifndef ZJR_CAMERA_
#define ZJR_CAMERA_

#include "../GraphicLib/Ray.h"

class Camera
{
public:
	Camera();
	virtual ~Camera();

	void							update();
	void							update(const Point &eye, const Point &lookAt);
	Ray								GeneratedRay(int x, int y, int bufferWidth, int bufferheight, int screenWidth, int screenHeight);

private:
	Point							eyePosition;
	Point							lookAtPosition;
	Vector3							up;
	Vector3							u, v, w;
	float							eyeDistance;
};

#endif
