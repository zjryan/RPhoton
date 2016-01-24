#ifndef ZJR_SCENE_
#define ZJR_SCENE_

#include "vector"

class Ray;
class Color;
class Light;
class Camera;
class Geometry;
class SkyBox;

class Scene
{
public:
	SkyBox*							skyBox;
	std::vector<Geometry*>			geometries;
	std::vector<Light*>				lights;
	Light*							environmentLight;

	Scene();
	Scene(const Scene &s) = delete;
	~Scene();

	Color							Shaded(const Ray &ray);
	void							add(Geometry *geometry);
	void							add(Light *light);

private:
	void							deleteGeometries();
	void							deleteLights();
};

#endif
	