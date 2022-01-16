#ifndef _TERRAIN_HXX_
#define _TERRAIN_HXX_

#include "../Geometries/MyTerrainGeometry.hxx"
#include "../Entity.hh"
/// <h2> Author: Kia Kalani </h2>
/// <strong> Student ID: 101145220 </strong>
/// <summary>
/// <code>Terrain</code> class is used for creating a terrain that
/// the tank could drive on it.
/// </summary>
/// <strong> Last Revised: Friday, December 17th, 2021 </strong>
class Terrain: public Entity
{
    private:
    MyTerrainGeometry *terrain_geom;

    public:
    Terrain();
    ~Terrain();

    float get_terrain_height(const glm::vec3&) const;

    bool terrain_collided(const Entity*&) const;

    void set_on_terrain(Entity*&) const;

    float max_x() const;
    float max_z() const;
};


#endif
