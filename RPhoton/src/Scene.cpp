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
	Memory::safeDelete(environmentLight);
	Memory::safeDelete(skyBox);
	deleteGeometries();
	deleteLights();
}

Color Scene::Shaded(const Ray &ray)
{
	Color backgroundColor = skyBox->skyColor(ray);
	ShadingInfo interFinal;

	auto geoSize = geometries.size();
	for (int i = 0; i < geoSize; i++)
	{
		ShadingInfo idata;
		if (geometries[i]->intersected(ray, idata.t))
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
		interFinal.updateShadingInfo(ray);
		auto hitPoint = interFinal.hitPoint;
		auto interGeo = interFinal.hitGeo;
		auto hitNormal = interFinal.hitNormal;
		auto TexCoord = interFinal.texCoord;

		auto lightSize = lights.size();
		auto retColor = interGeo->material->surfaceColor(TexCoord) * environmentLight->intensity(hitPoint, hitNormal);
		
		for (int i = 0; i < lightSize; i++)
		{
			retColor += lights[i]->intensity(hitPoint, hitNormal);
		}
		return retColor;
	}

	return backgroundColor;
}

void Scene::add(Geometry *geometry)
{
	geometries.push_back(geometry);
}

void Scene::add(Light *light)
{
	lights.push_back(light);
}

void Scene::deleteGeometries()
{
	size_t vecSize = geometries.size();
	for (unsigned int i = 0; i < vecSize; i++)
	{
		Memory::safeDelete(geometries[i]);
	}
}

void Scene::deleteLights()
{
	size_t vecSize = lights.size();
	for (unsigned int i = 0; i < vecSize; i++)
	{
		Memory::safeDelete(lights[i]);
	}
}