#include "Camera.h"

Camera::Camera()
	:	eyePosition(0.0, -1000.0f, 0.0f),
		lookAtPosition(0.0f, 0.0f, 0.0f),
		up(0.0f, 0.0f, 1.0f),
		eyeDistance(500.0f)
{
	Update();
}

Camera::~Camera()
{
}

inline void Camera::Update()
{
	w = eyePosition - lookAtPosition;
	eyeDistance = w.Length();
	w.Normalize();
	u = up.Cross(w);
	u.Normalize();
	v = w.Cross(u);
	v.Normalize();
}

inline void Camera::Update(const Point& eye, const Point& lookAt)
{
	eyePosition = eye;
	lookAtPosition = lookAt;
	Update();
}

Ray Camera::GenerateRay(int x, int y, int bufferWidth, int bufferHeight, int screenWidth, int screenHeight)
{
	//compute pixel size
	float widthRatio = static_cast<float>(screenWidth) / bufferWidth;
	float heightRatio = static_cast<float>(screenHeight) / bufferHeight;

 	float X = widthRatio * (x - bufferWidth * 0.5f + 0.5f);
	float Y = heightRatio * (y - bufferHeight * 0.5f + 0.5f);

	//compute pixel position in viewplane
	Point ori(eyePosition);
	Vector dir = u * X + v * Y - w * 600.0f;
	dir.Normalize();

	return Ray(ori, dir);
}