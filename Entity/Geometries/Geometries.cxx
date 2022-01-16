#include "Geometries.hxx"
#include "CylinderGeometry.hxx"
#include "QuadGeometry.hxx"
#include "SphereGeometry.hxx"

Geometries::Geometries()
{
    sphere = new SphereGeometry;
    quad = new QuadGeometry;
    cylinder = new CylinderGeometry;
}

Geometries::~Geometries()
{
    delete sphere;
    delete quad;
    delete cylinder;
}

Geometry *Geometries::CYLINDER() const
{
    return cylinder;
}

Geometry *Geometries::SPHERE() const
{
    return sphere;
}

Geometry *Geometries::QUAD() const
{
    return quad;
}