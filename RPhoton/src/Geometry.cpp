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

Geometry& Geometry::operator=(const Geometry &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	material = rhs.material;
	return *this;
}
