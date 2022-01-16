#ifndef _GEOMETRIES_HXX_
#define _GEOMETRIES_HXX_
#include "../Geometry.hh"
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// Geometry container class
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class Geometries
{
    private: // Excludes Terrain
    Geometry *sphere;
    Geometry *cylinder;
    Geometry *quad;
    public:
    Geometries();
    ~Geometries();

    Geometry *SPHERE() const;
    Geometry *CYLINDER() const;
    Geometry *QUAD() const;
};
#endif