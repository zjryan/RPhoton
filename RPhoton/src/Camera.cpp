#include "Camera.h"

Camera::Camera()
	:	eyePosition(0.0, -1000.0f, 0.0f),
		lookAtPosition(0.0f, 0.0f, 0.0f),
		up(0.0f, 0.0f, 1.0f),
		eyeDistance(500.0f)
{
	update();
}

Camera::~Camera()
{
}

inline void Camera::update()
{
	w = eyePosition - lookAtPosition;
	eyeDistance = w.length();
	w.normalize();
	u = up.cross(w);
	u.normalize();
	v = w.cross(u);
	v.normalize();
}

inline void Camera::update(const Point& eye, const Point& lookAt)
{
	eyePosition = eye;
	lookAtPosition = lookAt;
	update();
}

Ray Camera::GeneratedRay(int x, int y, int bufferWidth, int bufferHeight, int screenWidth, int screenHeight)
{
	//compute pixel size
	float widthRatio = static_cast<float>(screenWidth) / bufferWidth;
	float heightRatio = static_cast<float>(screenHeight) / bufferHeight;

 	float X = widthRatio * (x - bufferWidth * 0.5f + 0.5f);
	float Y = heightRatio * (y - bufferHeight * 0.5f + 0.5f);

	//compute pixel position in viewplane
	Point ori(eyePosition);
	Vector3 dir = u * X + v * Y - w * 600.0f;
	dir.normalize();

	return Ray(ori, dir);
}