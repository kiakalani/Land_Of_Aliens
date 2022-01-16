#include "Terrain.hxx"
#include "../../Texture/Texture.hh"
#include "../../World/GameWorld.hh"
Terrain::Terrain(): Entity(NULL, NULL,
GameDisplay::get_loaded_textures()->TERRAIN())
{
    terrain_geom = new MyTerrainGeometry;
    shape = terrain_geom;
    shader = Shader::read_file((char*)SHADER_PATH"/Entity/Terrain/vertex.glsl", (char*)SHADER_PATH"/Entity/Terrain/fragment.glsl");
    set_scale(glm::vec3(100.0f, 1.0f, 100.0f));
}
Terrain::~Terrain()
{
    delete terrain_geom;
    delete shader;
    if (texture) delete texture;
}

float Terrain::get_terrain_height(const glm::vec3 &v) const
{
    float xpos = v[0] / get_scale()[0];
    float zpos = v[2] / get_scale()[2];

    return terrain_geom->get_y(xpos, zpos); 
}

bool Terrain::terrain_collided(const Entity *&entity) const
{
    glm::vec3 low = (entity->get_position() - (entity->get_scale() / 2.0f));
    return low[1] < get_terrain_height(low);
}

void Terrain::set_on_terrain(Entity *&e) const
{
    if (terrain_collided((const Entity*&)e))
    {
        glm::vec3 trans = e->get_position();
        glm::vec3 scale = e->get_scale();

        e->set_translate(glm::vec3(trans[0], get_terrain_height(trans) + scale[1] * 0.5f, trans[2]));    
    }
}


float Terrain::max_z() const
{
    return terrain_geom->max_z() * get_scale()[2];
}

float Terrain::max_x() const
{
    return terrain_geom->max_x() * get_scale()[0];
}