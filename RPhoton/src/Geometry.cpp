#include "Geometry.h"

Geometry::Geometry()
	:	material()
{
	material = new Material();
}

Geometry::Geometry(Material *material_)
	:	material(material_)
{
}

Geometry::Geometry(const Geometry &geo)
	:	material(geo.material)
{
}

Geometry::~Geometry()
{
	delete material;
}
