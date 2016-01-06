#include "Scene.h"
#include "Light.h"
#include "Utilities.h"
#include "Geometry.h"
#include "Material.h"
#include "ShadingInfo.h"
#include "Cube.h"
#include "../GraphicLib/Ray.h"
#include "../GraphicLib/Color.h"
#include "../GraphicLib/Normal.h"

#include <iostream>
using namespace std;

Scene::Scene()
	:	geometries(),
		lights(),
		skyBox(nullptr),
		environmentLight(nullptr)
{
	skyBox = new SkyBox();
}

Scene::~Scene()
{
	Memory::SafeDelete(environmentLight);
	Memory::SafeDelete(skyBox);
	deleteGeometries();
	deleteLights();
}

Color Scene::Shading(const Ray &ray)
{
	Color backgroundColor = skyBox->GetSkyColor(ray);
	ShadingInfo interFinal;

	auto geoSize = geometries.size();
	for (int i = 0; i < geoSize; i++)
	{
		ShadingInfo idata;
		if (geometries[i]->Intersect(ray, idata.t))
		{
			interFinal.isIntersected = true;
			if (idata.t < interFinal.t)
			{
				interFinal.t = idata.t;
				interFinal.hitGeo = geometries[i];
			}
		}
	}

	if (interFinal.isIntersected)
	{
		interFinal.UpdateShadingInfo(ray);
		auto hitPoint = interFinal.hitPoint;
		auto interGeo = interFinal.hitGeo;
		auto hitNormal = interFinal.hitNormal;

		auto lightSize = lights.size();
		auto retColor = interGeo->material->color * environmentLight->I(hitPoint, hitNormal);
		
		for (int i = 0; i < lightSize; i++)
		{
			retColor += lights[i]->I(hitPoint, hitNormal);
		}
		return retColor;
	}

	return backgroundColor;
}

void Scene::Add(Geometry *geometry)
{
	geometries.push_back(geometry);
}

void Scene::Add(Light *light)
{
	lights.push_back(light);
}

void Scene::deleteGeometries()
{
	size_t vecSize = geometries.size();
	for (unsigned int i = 0; i < vecSize; i++)
	{
		Memory::SafeDelete(geometries[i]);
	}
}

void Scene::deleteLights()
{
	size_t vecSize = lights.size();
	for (unsigned int i = 0; i < vecSize; i++)
	{
		Memory::SafeDelete(lights[i]);
	}
}