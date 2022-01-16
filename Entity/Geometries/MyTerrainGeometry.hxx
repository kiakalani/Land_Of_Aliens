#ifndef _MY_TERRAIN_HXX_
#define _MY_TERRAIN_HXX_
#include "../Geometry.hh"
#include <stdint.h>
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// Terrain geometry
/// </summary>
/// <strong> Last Revised: Thursday, November 18th, 2021 </strong>
class MyTerrainGeometry: public Geometry
{
    private:
    // gives the noise value according to x and z of the given vec3
    float noise_value(const glm::vec3&) const;
    uint32_t width, depth, height;
    float *terrain_ys;
    public:
    MyTerrainGeometry(uint32_t = 100, uint32_t = 50, uint32_t = 100);
    ~MyTerrainGeometry();
    // The y according to given x and y
    float get_y(const float &x, const float &z) const;

    // gives the width and depth
    float max_x() const;
    float max_z() const;

};
#endif