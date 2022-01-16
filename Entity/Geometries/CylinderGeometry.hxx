#ifndef _CYLINDER_GEOMETRY_HXX_
#define _CYLINDER_GEOMETRY_HXX_
#include "../Geometry.hh"
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// Cylinder geometry
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class CylinderGeometry: public Geometry
{
    public:
    CylinderGeometry(float height = 1.0, float circle_radius = 0.6, int num_loop_samples = 90, int num_circle_samples = 30);
    ~CylinderGeometry();
};
#endif