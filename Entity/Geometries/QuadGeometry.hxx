#ifndef _QUAD_HXX_
#define _QUAD_HXX_
#include "../Geometry.hh"

/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>QuadGeometry</code> is the Quad geometry
/// that is provided in the code samples within the
/// <code>ResourceManager</code> class.<br>
/// <strong> Note: </strong>
/// This class is derived from <code>Geometry</code>
/// class. For more information, please refer to 
/// <a href="../Geometry.hh"> its header file </a>
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class QuadGeometry: public Geometry
{
    public:
    QuadGeometry();
    ~QuadGeometry();
};
#endif
